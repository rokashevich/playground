#include <future>
#include <iostream>
struct Foo {
  Foo() : data(0) {}
  void sum(int i) { data += i; }
  int data;
};

void sss(int i) { std::cout << i << '\n'; }

int main() {
  Foo foo;
  auto f = std::async(&Foo::sum, &foo, 42);
  f.get();
  std::cout << foo.data << "\n";
  f = std::async(&sss, 43);
}