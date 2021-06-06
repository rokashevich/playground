/*
g++ init.cpp ; ./a.out
*/
#include <iostream>

int a;  // = 0

void f() {
  static int a;  // = 0
  int b;         // неопределено
  int c{};       // = 0
}

int main() {
  // int a{4.5};  // error: narrowing conversion!
  int b(4.5);  // = 4
  int c;       // неопределено
  return 0;
}
