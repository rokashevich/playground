/*
g++ const.cpp ; ./a.out
non const
const, counter=1
*/
#include <iostream>

class A {
  mutable int counter;

 public:
  A() : counter(0) {}
  void f() { std::cout << "non const" << std::endl; }
  void f() const {
    counter++;
    std::cout << "const, counter=" << counter << std::endl;
  }
};

int main() {
  A a;
  const A& b = a;
  a.f();
  b.f();
  return 0;
}
