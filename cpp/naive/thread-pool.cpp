// clang-format off
// https://github.com/sajeruk/ThreadPool/
#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <chrono>
#include <queue>
#include <condition_variable>
class ThreadPool{
  std::vector<std::thread> workers_;
  std::mutex m_;
  std::condition_variable cv_;
  std::queue<std::function<void()>> tasks_;
public:
  ThreadPool(int threads);
  ~ThreadPool();
  void AddTask(std::function<void()> lambda);
};

ThreadPool::ThreadPool(int threads){
  workers_.reserve(threads);
  for (auto i=0;i<threads;++i) workers_.emplace_back([this](){
    for(;;){
      std::function<void()> task; // void() может хранить лямбду
      {
        std::unique_lock<std::mutex> l{m_};
        cv_.wait(l, [this](){return !tasks_.empty();});
        task = tasks_.front(); // std::move?
        tasks_.pop();
      }
      task();
      cv_.notify_one();
    }
  });
}

ThreadPool::~ThreadPool(){
  for(auto& worker: workers_) worker.join();
}

void ThreadPool::AddTask(std::function<void()> lambda) {
  std::unique_lock<std::mutex> l{m_};
  tasks_.emplace(lambda);
  cv_.notify_one();
}

int main(){
  ThreadPool tp{5};
  for (int i=0;i<20;++i){
    tp.AddTask([i](){
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      std::cout << i << std::flush;});
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(10000));
  std::cout << "\nnew portion\n";
  for (int i=0;i<100;++i){
    tp.AddTask([i](){
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      std::cout << i << std::flush;});
  }
}