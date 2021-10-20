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
// g++ httpd.cpp -Iboost -lpthread -Lboost/lib -lboost_system -o httpd
// https://www.codeproject.com/articles/1007262/a-minimal-http-web-server-using-boost-asio
// clang-format on

#include <boost/asio.hpp>
#include <boost/process.hpp>
#include <iostream>
#include <thread>
#include <chrono>

using namespace boost;
using namespace boost::system;
using namespace boost::asio;
// using namespace boost::process;

class session {
  asio::streambuf buff;

 public:
  static void serve(std::shared_ptr<session> pThis, io_service& ios) {
    std::cout << "async_read_until(sock, buff, read_callback) // register "
                 "read_callback\n";
    // GET запрос имеет вид "GET /script.sh HTTP/1.1\r\n"
    asio::async_read_until(
        pThis->socket, pThis->buff, '\r',
        [pThis, &ios](const error_code& e, std::size_t s) {
          std::cout << "\read_callback begin\n";
          std::string line;
          std::istream stream{&pThis->buff};
          std::getline(stream, line, '\r');
          // ВЫПОЛНЕНИЕ СКРИПТА
          process::async_system(
              ios,
              [](boost::system::error_code err, int rc) {
                std::cout << "FINISHED\n";
              },
              "sleep 10");
          // ТУТ НАДО СФОРМИРОВАТЬ ПРАВИЛЬНЫЙ ЗАГОЛОВОК И ЗАПИСАТЬ В СОКЕТ
          std::string text{
              "HTTP/1.1 200 OK\r\ncontent-type: text/html\r\ncontent-length: "
              "3\r\n\r\n200"};
          asio::async_write(pThis->socket,
                            boost::asio::buffer(text.c_str(), text.length()),
                            [](const error_code& e, std::size_t s) {});
          std::cout << "\read_callback end\n";
        });
  }
  ip::tcp::socket socket;
  session(io_service& ios) : socket(ios) {}
};

void accept_and_run(ip::tcp::acceptor& acceptor, io_service& io_service) {
  std::shared_ptr<session> sesh = std::make_shared<session>(io_service);
  std::cout
      << "acceptor.async_accept(sock, accept_callback) // register callback\n";
  acceptor.async_accept(sesh->socket, [sesh, &acceptor, &io_service](
                                          const error_code& accept_error) {
    std::cout << "\naccept_callback begin\n";
    accept_and_run(acceptor, io_service);
    if (!accept_error) {
      session::serve(sesh, io_service);
    }
    std::cout << "accept_callback end\n\n";
  });
}

int main(int argc, const char* argv[]) {
  // Вынести в ключи через boost_program_options
  const int port{8080};
  const std::string script{"script.sh"};

  // Стандартная процедура запуска асинхронновго сервера на Boost.Asio.
  io_service ios;
  ip::tcp::endpoint endpoint{ip::tcp::v4(), port};
  ip::tcp::acceptor acceptor{ios, endpoint};

  std::cout << "acceptor.listen()\n";
  acceptor.listen();

  std::cout << "accept_and_run(acceptor, ios)\n";
  accept_and_run(acceptor, ios);

  std::cout << "ios.run()\n";
  ios.run();

  return 0;
}