#include <iostream>
struct S {
  int x, y;
  S(int a, int b) : S(a) {
    x = y = 3;
    std::cout << "2:(3,3)" << x << " " << y << "\n";
  }
  S(int a) : x(a + a), y(777) {
    std::cout << "1:(2,777)" << x << " " << y << "\n";
  }
};

int main() {
  S s(1, 2);
  std::cout << "1:(3,3)" << s.x << " " << s.y << "\n";
}