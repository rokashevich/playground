#include <iostream>
#include <utility>
class S {
 public:
  S() { std::cout << "default constructor" << std::endl; }
  S(const S& s) { std::cout << "copy constructor" << std::endl; }
  S(S&& s) { std::cout << "move constructor" << std::endl; }
};
int main() {
  S s;
  S copy_constructed{s};
  S move_constructed{std::move(s)};
  return 0;
}
