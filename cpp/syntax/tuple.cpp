#include <iostream>
#include <tuple>
int main() {
  auto t = std::make_tuple(1, 2, 3, std::string{"xxx"});
  std::cout << typeid(t).name() << std::endl;
  auto v2 = std::get<3>(t);
  std::cout << typeid(v2).name() << std::endl;
  std::cout << v2 << std::endl;
  // std::cout << v2 << '\n';
}