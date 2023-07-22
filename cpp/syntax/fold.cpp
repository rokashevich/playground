// g++ -std=c++17 fold.cpp
#include <climits>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

template <typename... Args>
void printer(Args&&... args) {
  (std::cout << ... << args) << '\n';
}

template <typename... Args>
void conjunction(Args&&... args) {
  std::cout << (... && args) << '\n';
}

int main() {
  printer(1, 2, 3, "abc");
  conjunction(true, true, true, 0);
}
