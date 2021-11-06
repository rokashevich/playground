#include <utility>  // std::move
class A {
  void* data = nullptr;

 public:
  A(const A& a) : data(a.data ? (new T(data)) : nullptr) {
    // data = new char(size); std::memcpy(data, a.data, size);
  }
  A(A&& a) {
    data = a.data;
    a.data = nullptr;
  }
};

int main() { return 0; }