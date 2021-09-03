#include <iostream>
#include <utility>
// clang-format off
class S {
 public:
  S() { std::cout << "default constructor\n"; }
  S(S& s) { std::cout << "copy constructor\n"; }
  S& operator=(S& s) { std::cout << "copy assignment\n"; return *this; }
  S(S&& s)noexcept{ std::cout << "move constructor\n"; }
  S& operator=(S&& s)noexcept{ std::cout << "move assignment\n"; return *this; }
};

int main() {
  S a; // Default constructor
  S b{a}; // Copy constructor
  a = b; // Copy assignment

  S c{std::move(b)}; // Move constructor
  c = std::move(a); // Move assignment
  return 0;
}
