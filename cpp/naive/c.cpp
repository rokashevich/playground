#include <iostream>
struct A {
  int i{};
  struct B {
    int j{};
  }
};
int main() {
  A::B b{};
  b.fn();  // There is no @A, so there is no @i for @A::B::fn to access.
}