// clang-format off
// g++ echo-client-server.cpp -lpthread -lboost_system -lboost_thread -lboost_program_options
// https://github.com/Vasilui/habrahabr/tree/master/Boost.Asio_C%2B%2B_Network_Programming/Chapter_3
// https://habr.com/ru/post/195794/
// clang-format on
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <memory>
#include <string>
using namespace boost::asio;
using namespace boost::posix_time;
using namespace boost::program_options;
using boost::system::error_code;
io_service service;

//=============================================================================
// TCP SYNC
size_t read_complete(char* buff, const error_code& err, size_t bytes) {
  if (err) return 0;
  bool found = std::find(buff, buff + bytes, '\n') < buff + bytes;
  // we read one-by-one until we get to enter, no buffering
  return found ? 0 : 1;
}
//-----------------------------------------------------------------------------
// SERVER
void tss_handle_connections() {
  ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8001));
  char buff[1024];
  while (true) {
    ip::tcp::socket sock(service);
    acceptor.accept(sock);
    int bytes = read(sock, buffer(buff), [&](auto& err, auto bytes) {
      return read_complete(buff, err, bytes);
    });
    std::string msg(buff, bytes);
    std::cout << "got " << msg;
    sock.write_some(buffer(msg));
    sock.close();
  }
}
//-----------------------------------------------------------------------------
// CLIENT
ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 8001);
void sync_echo(std::string msg) {
  msg += "\n";
  ip::tcp::socket sock(service);
  sock.connect(ep);
  sock.write_some(buffer(msg));
  char buf[1024];
  int bytes = read(sock, buffer(buf), [&](auto& err, auto bytes) {
    return read_complete(buf, err, bytes);
  });
  std::string copy(buf, bytes - 1);
  msg = msg.substr(0, msg.size() - 1);
  std::cout << "server echoed our " << msg << ": "
            << (copy == msg ? "OK" : "FAIL") << std::endl;
  sock.close();
}
//=============================================================================
// TCP ASYNC SERVER
#define MEM_FN(x) boost::bind(&self_type::x, shared_from_this())
#define MEM_FN1(x, y) boost::bind(&self_type::x, shared_from_this(), y)
#define MEM_FN2(x, y, z) boost::bind(&self_type::x, shared_from_this(), y, z)
class talk_to_client : public std::enable_shared_from_this<talk_to_client>,
                       boost::noncopyable {
  typedef talk_to_client self_type;
  talk_to_client() : sock_(service), started_(false) {}

 public:
  typedef boost::system::error_code error_code;

  static ip::tcp::acceptor& acceptor() {
    static ip::tcp::acceptor acceptor(service,
                                      ip::tcp::endpoint(ip::tcp::v4(), 8001));
    return acceptor;
  };

  void start() {
    started_ = true;
    do_read();
  }

  static std::shared_ptr<talk_to_client> new_() {
    std::shared_ptr<talk_to_client> new_(new talk_to_client);
    return new_;
  }
  void stop() {
    if (!started_) return;
    started_ = false;
    sock_.close();
  }
  ip::tcp::socket& sock() { return sock_; }

 private:
  void on_read(const error_code& err, size_t bytes) {
    if (!err) {
      std::string msg(read_buffer_, bytes);
      std::cout << "got " << msg;
      // echo message back, and then stop
      do_write(msg + "\n");
    }
    stop();
  }

  void on_write(const error_code& err, size_t bytes) { do_read(); }
  void do_read() {
    async_read(sock_, buffer(read_buffer_), MEM_FN2(read_complete, _1, _2),
               MEM_FN2(on_read, _1, _2));
  }
  void do_write(const std::string& msg) {
    std::copy(msg.begin(), msg.end(), write_buffer_);
    sock_.async_write_some(buffer(write_buffer_, msg.size()),
                           MEM_FN2(on_write, _1, _2));
  }
  size_t read_complete(const boost::system::error_code& err, size_t bytes) {
    if (err) return 0;
    bool found = std::find(read_buffer_, read_buffer_ + bytes, '\n') <
                 read_buffer_ + bytes;
    // we read one-by-one until we get to enter, no buffering
    return found ? 0 : 1;
  }

 private:
  ip::tcp::socket sock_;
  enum { max_msg = 1024 };
  char read_buffer_[max_msg];
  char write_buffer_[max_msg];
  bool started_;
};

// Приём клентов.
void handle_accept(std::shared_ptr<talk_to_client> client,
                   const boost::system::error_code& err) {
  client->start();
  std::shared_ptr<talk_to_client> new_client = talk_to_client::new_();
  talk_to_client::acceptor().async_accept(new_client->sock(), [=](auto& err) {
    return handle_accept(new_client, err);
  });
}

int main(int argc, char* argv[]) {
  options_description desc("Options:");
  desc.add_options()("tss", "TCP Sync Server");
  desc.add_options()("tsc", "TCP Sync Client");
  desc.add_options()("tas", "TCP Async Server");
  variables_map vm;
  store(parse_command_line(argc, argv, desc), vm);
  notify(vm);

  if (vm.count("tss")) {
    std::cout << "TCP Sync Server\n";
    tss_handle_connections();
  } else if (vm.count("tsc")) {
    std::cout << "TCP Sync Client\n";
    std::vector<std::string> messages{"AA", "BB", "CC", "DD"};
    boost::thread_group threads;
    for (auto& message : messages) {
      threads.create_thread([=] { return sync_echo(message); });
      boost::this_thread::sleep(boost::posix_time::millisec(100));
    }
    threads.join_all();
  } else if (vm.count("tas")) {
    std::cout << "TCP Async Server\n";
    std::shared_ptr<talk_to_client> client = talk_to_client::new_();

    talk_to_client::acceptor().async_accept(
        client->sock(), [=](auto& err) { return handle_accept(client, err); });

    service.run();
  }
}