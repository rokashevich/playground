#include <iostream>
#include <sstream>
int main() {
  std::ostringstream oss{"-----\n"};
  oss << 1 << std::endl << 2;
  std::cout << oss.str();  // 1\n2--
  return 0;
}