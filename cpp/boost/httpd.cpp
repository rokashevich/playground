// clang-format off
//
// BOOST
// https://boostorg.jfrog.io/artifactory/main/release/1.77.0/source/boost_1_77_0.tar.bz2
// mkdir boost && cd boost
// wget http*boost_VERSION*.tar.bz2
// tar -xvf boost_VERSION*.tar.bz2
// cd boost_VERSION
// ./bootstrap.sh --with-libraries=system,program_options
// ./b2 --stagedir=. link=static runtime-link=static
// INCLUDE: boost_VERSION
// LIB: boost_VERSION/lib
//
// PROJECT
// g++ httpd.cpp -pedantic -Iboost -lpthread -Lboost/lib -lboost_system -o httpd
// https://www.codeproject.com/articles/1007262/a-minimal-http-web-server-using-boost-asio
// clang-format on

#include <boost/asio.hpp>
#include <boost/process.hpp>
#include <boost/process/async.hpp>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <regex>

using namespace boost;
using namespace boost::system;
using namespace boost::asio;
// using namespace boost::process;

class session {
  asio::streambuf buff;

 public:
  static void serve(std::shared_ptr<session> pThis, io_service& ios) {
    // К нам в сокет приходит GET запрос который по спецификации имеет следующий
    // вид: "GET /script.sh HTTP/1.1\r\n ..." Т.е. когда в бразуере пишешь
    // 127.0.0.1:8080/script.sh то отправляется запрос именно такого вида.
    // И непосредственно создание асинхронной задачи, функция serve по сути
    // обёртка что бы не утяжелять функцию accept_and_run.
    asio::async_read_until(
        pThis->socket, pThis->buff, '\r',  // читаем данные сокет до первого \r
        [pThis, &ios](const error_code& e, std::size_t s) {
          // Внутри callback-а, который вызывается, когда boost.asio считал GET
          // запрос до символа \r (то что дальше нам и не надо).

          // Находим в подстроке запроса название endpoint_name.
          std::istream stream{&pThis->buff};  //байты которые считались
          std::string request;  // выделим сюда подстроку название скрипта
          std::getline(stream, request,
                       '\r');  // request = GET /script.sh HTTP/1.1
          std::smatch match;
          if (!std::regex_search(request, match, std::regex(R"(GET /(.*) )"))) {
            std::cout << "bad request: " << request << std::endl;
            return;
          }
          const std::string endpoint_name{match.str(1)};

          // Логика запуска скрипта.
          // Исходное состояние: скрипт не запущен, количество подключенных
          // сессий ноль. Как только появляется первый коннект (одновременно
          // двух не может быть т.к. асинхронщина это не многопоточность, а один
          // поток!) - запускаем скрипт (асинхронную задачу с колбэком) и в
          // любом случае добавляем идентификатор обрабатываемой сессии в
          // статический массив sessions. По завершении скрипта выполняется
          // callback который в каждую сохранённую сессию пишет код возврата 200
          // ОК, что скрипт завершился, и обнуляем массив сессий - состояние
          // приводится к исходному.
          if (session::sessions.empty()) {
            pThis->c = boost::process::child(
                std::vector<std::string>{"/bin/sh", "/tmp/a"},
                boost::process::std_in = boost::process::null,
                boost::process::std_out = boost::process::null,
                boost::process::std_err = boost::process::null, ios,
                boost::process::on_exit([](int e, const std::error_code& ec) {
                  // Внутри callback после завершения процесса. Вывод скрипта
                  // игнорируем, e - код возврата.
                  // Итерируемся по всем сессиям, которые подключились в
                  // процессе выполнения скрипта и каждому отправляем заголовок
                  // о завершении.
                  const std::string text{
                      "HTTP/1.1 200 OK\r\ncontent-type: "
                      "text/html\r\ncontent-length: "
                      "3\r\n\r\n200"};
                  for (auto sesh : session::sessions) {
                    asio::async_write(
                        sesh->socket,
                        boost::asio::buffer(text.c_str(), text.length()),
                        [](const error_code& e, std::size_t s) {});
                  }
                  // Очищаем сессии.
                  session::sessions.clear();
                }));
          }
          session::sessions.push_back(pThis);
        });
  }
  boost::process::child c;
  static std::vector<std::shared_ptr<session>> sessions;
  ip::tcp::socket socket;
  session(io_service& ios) : socket(ios) {}
};
std::vector<std::shared_ptr<session>> session::sessions = {};

void accept_and_run(ip::tcp::acceptor& acceptor, io_service& io_service) {
  // Заводим сессию для ещё неподключенного соединения.
  std::shared_ptr<session> sesh = std::make_shared<session>(io_service);

  // Непосредственно задача для воркера - принять соединение и выполнить
  // callback, данная функция неблокирующая, сразу же выходит. При первом
  // запуске внутри main() управление передаётся ios.run(), в последующих
  // случаях просто завершается callback и уже запущенный ios.run смотрит,
  // есть ли ещё задачи.
  acceptor.async_accept(sesh->socket, [sesh, &acceptor, &io_service](
                                          const error_code& accept_error) {
    // Внутри callback, значит какое-то соединение принято, и по завершению
    // callback-а у воркера не останется задач и он завершит свою работу.
    // Поэтому подсовыываем воркеру повторную задачу ожидать следующее
    // соединение. Когда оно примется - еще следующее. И т.д.
    accept_and_run(acceptor, io_service);

    // Если соединение успешно принято - кидаем в пул воркера еще одну
    // асинхронную задачу по чтению запроса, который пришёл к нам в сокет.
    if (!accept_error) session::serve(sesh, io_service);
  });
}

int main(int argc, const char* argv[]) {
  // Вынести в ключи через boost_program_options
  const int port{8080};

  // Стандартная процедура запуска асинхронновго сервера на Boost.Asio.
  io_service ios;
  ip::tcp::endpoint endpoint{ip::make_address("127.0.0.1"),
                             port};  // ip::tcp::v4() на все интерфейсы
  ip::tcp::acceptor acceptor{ios, endpoint};
  acceptor.listen();  //переводим сокет в режим прослушивания
  accept_and_run(acceptor, ios);  //добавляем первую задачу воркеру
  ios.run();                      //запускаем воркер

  return 0;
}