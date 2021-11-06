// clang-format off
#include <chrono>
#include <condition_variable>  // std::condition_variable
#include <iostream>            // std::cout
#include <mutex>               // std::mutex, std::unique_lock
#include <thread>              // std::thread
std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id(int id) {
  std::unique_lock<std::mutex> lck(mtx);

  std::cout << id << std::flush;
  
  cv.wait(lck); // блокируется до notify_all/notify_one, по notify - блокирует lck

  std::cout << id << std::flush;
}               // по выходу из области видимости lck разблокируется

int main() {
  std::thread threads[10];
  for (int i = 0; i < 10; ++i) threads[i] = std::thread(print_id, i); // запускаем треды - они блокируются в ожидании notify_all/notify_one
  
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  

  cv.notify_one();
  cv.notify_one();
  cv.notify_one();
  cv.notify_one();
  cv.notify_one();
  cv.notify_one();
  cv.notify_one();
  cv.notify_one();
  cv.notify_one();
  cv.notify_one();

  for (auto& th : threads) {
    std::cout << '*' << std::flush;
    th.join();
  }

  return 0;
}