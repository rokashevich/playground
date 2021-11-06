// clang-format off
#include <functional>  // std::ref
#include <future>      // std::promise, std::future
#include <iostream>    // std::cout
#include <thread>      // std::thread
#include <chrono>

void tf(std::promise<int>& prom) { 
  
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  prom.set_value(777);
  // prom.set_value(111); // НЕЛЬЗЯ ВТОРОЙ РАЗ!
}

int main() {
  std::promise<int> prom;            // создали promise  
  std::thread t(tf, std::ref(prom)); // отправили promise в трэд

  std::future<int> fut = prom.get_future();  // связали promise с future
  std::cout << fut.get() << '\n'; // блокируется, пока не сделается promise
  // fut.get(); // НЕЛЬЗЯ ВТОРОЙ РАЗ!

  std::cout << "Wait tread join\n";
  t.join();
  return 0;
}