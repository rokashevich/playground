// clang-format off
#include <functional>  // std::ref
#include <future>      // std::async
#include <iostream>    // std::cout
#include <thread>      // std::thread
#include <chrono>

int tf(int i) { 
  std::cout << "begin " << i << '\n';
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::cout << "end " << i << '\n';
  return i+i;
}

int main() {
  auto a{std::async(std::launch::async,tf,1)};
  auto b{std::async(std::launch::async,tf,2)};
  std::cout << "Now wait\n";
  std::cout << a.get() << b.get() << '\n';
  return 0;
}