#include <exception>
#include <iostream>

struct A {
  A() { std::cout << "A::A" << std::endl; }
  ~A() { std::cout << "A::~A" << std::endl; }
};

struct B : A {
  B() {
    std::cout << "B::B" << std::endl;
    throw std::exception();
  }
  ~B() { std::cout << "B::~B" << std::endl; }
};

int main() {
  try {
    B b;
  } catch (const std::exception&) {
    std::cout << "std::exception" << std::endl;
  }
}
