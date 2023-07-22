#include <boost/asio.hpp>
#include <fstream>
#include <iostream>

constexpr std::size_t chunk_size = 16;

int main() {
  // Open the file for reading
  std::ifstream file("data_big.csv", std::ios::binary);
  if (!file) {
    std::cerr << "Error opening file" << std::endl;
    return 1;
  }

  // Create an io_context for Boost Asio
  boost::asio::io_context io_context;

  // Create a socket and connect to the server
  boost::asio::ip::tcp::socket socket(io_context);
  socket.connect({boost::asio::ip::make_address("127.0.0.1"), 12345});

  // Allocate a buffer for reading the file
  std::vector<char> buffer(chunk_size);

  // Read the file in chunks and send each chunk over the socket
  while (file) {
    file.read(buffer.data(), chunk_size);
    size_t count = file.gcount();
    std::cout << "*" << count << "\n" << std::endl;
    if (!count) break;
    size_t n = boost::asio::write(socket, boost::asio::buffer(buffer, count));
  }
  buffer[0] = '\0';
  auto len = boost::asio::write(socket, boost::asio::buffer(buffer, 1));
  std::cout << "final len = " << len << std::endl;

  return 0;
}