#include <cstdio>
template <int N>
struct Factorial {
  enum { value = N * Factorial<N - 1>::value };
};
template <>
struct Factorial<0> {
  enum { value = 1 };
};
int main() {
  printf("%d\n", Factorial<10>::value);
  return 0;
}