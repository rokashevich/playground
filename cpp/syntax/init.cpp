// clang-format off
#include <iostream>
#include <string>
int a;  // = 0

void f() {
  static int a;  // = 0
  int b;         // неопределено
  int c{};       // = 0
}

struct S {
  int a{1};  //с с++11 так можно
  const static int as{2}; // можно только статик интеграл конст!
  //static int ass{2}; // нельзя 
  const char* c{"так можно"};
  // char* c{"так можно"}; // без const варнинг
  std::string s{"tak"};
};

int main() {
  // int a{4.5};  // error: narrowing conversion!
  int b(4.5);  // = 4
  int c;       // неопределено
  std::cout << S{}.s << std::endl;
  return 0;
}
