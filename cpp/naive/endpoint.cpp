// g++ endpoint.cpp -lpthread -lboost_system -lboost_thread
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <iostream>
using namespace boost::asio;

// g++ endpoint.cpp -lpthread -lboost_system -lboost_thread
// test
// dispatched 1
// dispatched 2
// io_service service;
// void dispatched_func_1() { std::cout << "dispatched 1" << std::endl; }
// void dispatched_func_2() { std::cout << "dispatched 2" << std::endl; }
// void test(boost::function<void()> func) {
//   std::cout << "test" << std::endl;
//   service.dispatch(dispatched_func_1);
//   func();
// }
// void service_run() { service.run(); }
// int main(int argc, char* argv[]) {
//   test(service.wrap(dispatched_func_2));
//   boost::thread th(service_run);
//   boost::this_thread::sleep(boost::posix_time::millisec(500));
//   th.join();
// }

// Диспатч вызывает обработчик сразу же!
// func called, i= 0
// func called, i= 2
// func called, i= 4
// func called, i= 6
// func called, i= 8
// run_dispatch_and_post finished
// func called, i= 1
// func called, i= 3
// func called, i= 5
// func called, i= 7
// func called, i= 9
//
// io_service service;
// void func(int i) { std::cout << "func called, i= " << i << std::endl; }
// void run_dispatch_and_post() {
//   for (int i = 0; i < 10; i += 2) {
//     service.dispatch(boost::bind(func, i));  // 0 2 4 6 8
//     service.post(boost::bind(func, i + 1));  // 1 3 5 7 9
//   }
//   std::cout << "run_dispatch_and_post finished\n";
// }
// int main(int argc, char* argv[]) {
//   service.post(run_dispatch_and_post);
//   service.run();
// }

// Задачи в каждом странде выполняеются ПОСЛЕДОВАТЕЛЬНО!
//
// func1 called, i=0/7fdb6a6e1700
// func2 called, i=5/7fdb69ee0700
// func1 called, i=1/7fdb696df700
// func1 called, i=3/7fdb696df700
// func1 called, i=4/7fdb696df700
// func1 called, i=2/7fdb696df700
// func2 called, i=6/7fdb69ee0700
// func2 called, i=7/7fdb69ee0700
// func2 called, i=9/7fdb69ee0700
// func2 called, i=8/7fdb69ee0700
//
// io_service service;
// void func1(int i) {
//   std::cout << "func1 called, i=" << i << "/" << boost::this_thread::get_id()
//             << std::endl;
// }
// void func2(int i) {
//   std::cout << "func2 called, i=" << i << "/" << boost::this_thread::get_id()
//             << std::endl;
// }
// void worker_thread() { service.run(); }
// int main(int argc, char* argv[]) {
//   io_service::strand strand_one(service), strand_two(service);
//   for (int i = 0; i < 5; ++i)
//     service.post(strand_one.wrap(boost::bind(func1, i)));
//   for (int i = 5; i < 10; ++i)
//     service.post(strand_two.wrap(boost::bind(func2, i)));
//   boost::thread_group threads;
//   for (int i = 0; i < 3; ++i) threads.create_thread(worker_thread);
//   boost::this_thread::sleep(boost::posix_time::millisec(500));
//   threads.join_all();
// }

// 10 задач выполняются 3-мя воркерами.
//
// io_service service;
// void func(int i) { std::cout << "func called, i= " << i << std::endl; }
// void worker_thread() { service.run(); }
// int main(int argc, char* argv[]) {
//   for (int i = 0; i < 10; ++i) service.post(boost::bind(func, i));
//   boost::thread_group threads;
//   for (int i = 0; i < 3; ++i) threads.create_thread(worker_thread);
//   // wait for all threads to be created
//   boost::this_thread::sleep(boost::posix_time::millisec(500));
//   threads.join_all();
// }