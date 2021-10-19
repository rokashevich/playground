// clang-format off
// g++ echo-client-server.cpp -lpthread -lboost_system -lboost_thread -lboost_program_options
// g++ httpd.cpp -lpthread -lboost_system -o httpd
// https://www.codeproject.com/articles/1007262/a-minimal-http-web-server-using-boost-asio

#include <boost/asio.hpp>
#include <iostream>

using namespace boost;
using namespace boost::system;
using namespace boost::asio;

class session {
  asio::streambuf buff;
public:
  static void read_first_line(std::shared_ptr<session> pThis) {
    std::cout << "async_read_until(sock, buff, read_callback) // register read_callback\n";
    // GET запрос имеет вид "GET /script.sh HTTP/1.1\r\n"
    asio::async_read_until(pThis->socket, pThis->buff, '\r',
                           [pThis](const error_code& e, std::size_t s) {
                             std::cout << "\read_callback begin\n";
                             std::string line;
                             std::istream stream{&pThis->buff};
                             std::getline(stream, line, '\r');
                             // ТУТ НАДО СФОРМИРОВАТЬ ПРАВИЛЬНЫЙ ЗАГОЛОВОК И ЗАПИСАТЬ В СОКЕТ
                             asio::async_write(pThis->socket, boost::asio::buffer(line.c_str(), line.length()),
                             [](const error_code& e, std::size_t s){});
                             std::cout << "\read_callback end\n";
                           });
  }
  ip::tcp::socket socket;
  session(io_service& io_service) : socket(io_service) {}
};

void accept_and_run(ip::tcp::acceptor& acceptor, io_service& io_service) {
  std::shared_ptr<session> sesh = std::make_shared<session>(io_service);
  std::cout << "acceptor.async_accept(sock, accept_callback) // register callback\n";
  acceptor.async_accept(sesh->socket, [sesh, &acceptor, &io_service](
                                          const error_code& accept_error) {
    std::cout << "\naccept_callback begin\n";
    accept_and_run(acceptor, io_service);
    if (!accept_error) {
      session::read_first_line(sesh);
    }
    std::cout << "accept_callback end\n\n";
  });
}

int main(int argc, const char* argv[]) {
  // Вынести в ключи через boost_program_options
  const int port{8080};
  const std::string script{"script.sh"};

  // Стандартная процедура запуска асинхронновго сервера на Boost.Asio.
  io_service io_service;
  ip::tcp::endpoint endpoint{ip::tcp::v4(), port};
  ip::tcp::acceptor acceptor{io_service, endpoint};

  std::cout << "acceptor.listen()\n";
  acceptor.listen();

  std::cout << "accept_and_run(acceptor, io_service)\n";
  accept_and_run(acceptor, io_service);

  std::cout << "io_service.run()\n";
  io_service.run();

  return 0;
}