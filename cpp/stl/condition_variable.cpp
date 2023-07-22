// clang-format off
 
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;

void worker_thread() {
  const auto id = std::this_thread::get_id();
  
  // Wait until main() sends data
  std::unique_lock<std::mutex> lk(m);
  std::cout << "\t" << id << " worker_thread cv.wait" << ", data=" << data << '\n';
  cv.wait(lk, [] { return ready; });

  // after the wait, we own the lock, worker thread processing data
  std::ostringstream ss;
  ss << data << ' ' << id << ' ';
  data = ss.str();
  std::cout << "\t" << id << " got lock, modified data=" << data << '\n';

  // Send data back to main()
  processed = true;
  // std::cout << "Worker thread signals data processing completed\n";

  // Manual unlocking is done before notifying, to avoid waking up
  // the waiting thread only to block again (see notify_one for details)
  lk.unlock();
  cv.notify_one();
}

int main() {
  // Создаём потоки
  std::thread worker1(worker_thread);
  std::thread worker2(worker_thread);
  std::thread worker3(worker_thread);

  std::this_thread::sleep_for(std::chrono::milliseconds(250));
  
  data = "Initial data;"; // send data to the worker thread
  {
    std::lock_guard<std::mutex> lk(m); // пока жив lk дерижт m залоченым
    ready = true;
    std::cout << "main() signals data ready for processing\n";
  }
  cv.notify_one();

  // wait for the worker
  {
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [] { return processed; });
  }
  std::cout << "Back in main(), data = " << data << '\n';
  std::cout << "wait 1\n";
  worker1.join();
  std::cout << "wait 2\n";
  worker2.join();
  std::cout << "wait 3\n";
  worker3.join();
  std::cout << "Back in main(), data = " << data << '\n';
}