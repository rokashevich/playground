#include <iostream>
struct S1 {
  char a;
  char b;
  long c;
};
int main() {
  std::cout << alignof(size_t) << '\n';

  std::cout << alignof(S1) << '\n';

  std::cout << alignof(int*) << '\n';

  std::cout << alignof(bool) << '\n';
  std::cout << alignof(char) << '\n';
  std::cout << alignof(int) << '\n';
  std::cout << alignof(long) << '\n';
  std::cout << alignof(long long) << '\n';
  std::cout << alignof(float) << '\n';
  std::cout << alignof(double) << '\n';
  std::cout << alignof(long double) << '\n';
}