/*
g++ printf.cpp ; ./a.out
*/
#include <stdio.h>
int main() {
  int a = 1;
  double b = 2;
  const char *c = "test";
  printf("%d %f %c\n", a, b, c);  // правильный вывод
  printf("%d %s %d\n", a, c, b);  // b выводится неправильно
  printf("%d %d %s\n", a, b, c);  // segfault (g++ 10.2.0)
  return 0;
}
