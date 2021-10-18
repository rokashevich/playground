#include <iostream>
// clang-format off
namespace n {
  auto a{1};
  enum n {b,c,d};
}
int main(){
  std::cout << n::a << n::c << std::endl;
  return 0;
}