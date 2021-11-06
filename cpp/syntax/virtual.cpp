#include <iostream>
class Base {
  virtual void method() { std::cout << "from Base" << std::endl; }

 public:
  virtual ~Base() { method(); }
  void baseMethod() { method(); }
};
class A : public Base {
  void method() { std::cout << "from A" << std::endl; }

 public:
  ~A() { method(); }
};

int main() {
  Base* base = new A;
  base->baseMethod();
  delete base;
}
// from A
// from A
// from Base
