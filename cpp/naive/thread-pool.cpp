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
  class Worker{
    ThreadPool& tp_;
  public:
    Worker(ThreadPool& tp);
    void operator()();
  };
  std::vector<std::thread> workers_;
  std::mutex m_;
  std::condition_variable cond_;
  std::queue<std::function<void()>> tasks_;
public:
  ThreadPool(int threads);
  ~ThreadPool();
  void AddTask(std::function<void()> lambda);
};

ThreadPool::ThreadPool(int threads){
  workers_.reserve(threads);
  for (auto i=0;i<threads;++i) workers_.emplace_back(Worker(*this));
}

ThreadPool::~ThreadPool(){
  for(auto& worker: workers_) worker.join();
}

void ThreadPool::AddTask(std::function<void()> lambda) {
  {
    std::unique_lock<std::mutex> l{m_};
    tasks_.emplace(lambda);
  }
}

ThreadPool::Worker::Worker(ThreadPool& tp):tp_{tp} {}

void ThreadPool::Worker::operator()(){
  std::cout << "Worker started operator()()\n";
  for(;;){
    std::function<void()> task; // void() может хранить лямбду
    {
      std::unique_lock<std::mutex> l{tp_.m_};
      if (!tp_.tasks_.empty()){//DEL
        task = tp_.tasks_.front(); // std::move?
        tp_.tasks_.pop();
      }//DEL
    }
    if (task) task(); //CHANGE
  }
}

int main(){
  ThreadPool tp{5};
  for (int i=0;i<10;++i){
    tp.AddTask([i](){
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      std::cout << i << std::flush;});
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::cout << "\nnew portion\n";
  for (int i=0;i<10;++i){
    tp.AddTask([i](){
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      std::cout << i << std::flush;});
  }
}