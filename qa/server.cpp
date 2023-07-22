#include <algorithm>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
std::vector<std::string> split(const std::string& s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream token_stream(s);
  while (std::getline(token_stream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

constexpr std::size_t chunk_size = 24;
std::string leftovers{""};

void handle_read(const boost::system::error_code& e, std::size_t len,
                 boost::asio::streambuf& b, boost::asio::ip::tcp::socket& s) {
  std::cout << "e=" << e << "b.size()=" << b.size() << " len=" << len
            << std::endl;

  std::istream stream(&b);
  std::string line;
  while (std::getline(stream, line)) {
    if (!stream.good())
      leftovers = line;
    else {
      line = leftovers + line;
      std::cout << "line=[" << line << "]" << std::endl;
      leftovers = "";
    }
  }
  if (e == boost::asio::error::not_found) {
    boost::asio::async_read_until(
        s, b, 0, [&b, &s](const boost::system::error_code& e, std::size_t len) {
          handle_read(e, len, b, s);
        });
  } else {
    if (leftovers.size())
      std::cout << "line=[" << leftovers << "]" << std::endl;
  }
}

int main() {
  // Initialize the I/O service and acceptor.
  boost::asio::io_service ioservice;
  boost::asio::ip::tcp::acceptor acceptor(
      ioservice,
      boost::asio::ip::tcp::endpoint(
          boost::asio::ip::address::from_string("127.0.0.1"), 12345));

  // Accept a new connection.
  boost::asio::ip::tcp::socket s(ioservice);
  acceptor.accept(s);

  // Start the first asynchronous read.
  boost::asio::streambuf b{chunk_size};

  // boost::array<char, 8> b;
  boost::asio::async_read_until(
      s, b, '\0',
      [&b, &s](const boost::system::error_code& e, std::size_t len) {
        handle_read(e, len, b, s);
      });

  // Run the I/O service to start the asynchronous operation.
  ioservice.run();

  return 0;
}
