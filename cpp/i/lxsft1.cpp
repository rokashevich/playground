#include <cstdio>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
int main() {
  auto f = [](int*& p) { p = new int[3]{}; };
  int* p = nullptr;
  f(p);
  for (int i = 0; i < 3; ++i) std::cout << p[i] << std::endl;

  class A {};
  class B : A {};
  A a;
  B b;
  std::cout << "sizeof(a)=" << sizeof(a) << "\nsizeof(b)=" << sizeof(b) << '\n';

  struct C {
    C() { std::cout << "ctor\n"; }
    ~C() { std::cout << "dtor\n"; }
  };
  auto f2 = []() { return std::shared_ptr<C>{new C{}}; };
  auto sp2 = f2();

  auto deleter = [](C* p) -> void {
    delete p;
    printf("deletered\n");
  };
  std::unique_ptr<C, decltype(deleter)> d1{new C{}, deleter};
  std::unique_ptr<C, std::function<void(C*)>> d(new C[3]{}, [](C* p) {
    printf("deletered begin\n");
    delete[] p;
    printf("deletered end\n");
  });

  auto sdeleter = [](C* p) {
    printf("sdeleter\n");
    delete p;
  };
  std::shared_ptr<C> sp_w_d{new C, sdeleter};

  // std::move(t) == static_cast<T&&>(t)
  std::unique_ptr<int> x;
  std::unique_ptr<int> z{std::move(x)};
  std::unique_ptr<int> y{static_cast<std::unique_ptr<int>&&>(z)};

  return 0;
}