// clang-format off
#include <iostream>
typedef void (*Fptr)();
struct N{
  int x{3};
  ~N(){std::cout << "delete\n";}
};
auto factory(){
  N n;
  std::cout << n.x << std::endl;
  return [&](){
    std::cout << n.x << std::endl;
  };
}
int main(){
  auto f = factory();
  std::cout << "after\n";
  f();
  return 0;
}