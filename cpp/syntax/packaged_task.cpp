// clang-format off
#include <iostream>     // std::cout
#include <future>       // std::packaged_task, std::future
#include <chrono>       // std::chrono::seconds
#include <thread>       // std::thread, std::this_thread::sleep_for

// count down taking a second for each value:
void f (int a, int b) {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << a+b << '\n';
}

int main ()
{
  std::packaged_task<void(int,int)> task{f};   // настроили packaged_task
  
  std::cout << "Call in the same thread(main):\n";
  task(2,2); // блокирует пока не выполнится функция
  std::cout << "Reset & call in another thread:\n";
  task.reset();

  std::future<void> fut = task.get_future();   // получили из него future
  std::thread th(std::move(task),1,2); // copy-конструктор удалён, только move!

  fut.get();   

  th.join();

  return 0;
}