// clang-format off
#include <iostream>
struct B {
  int x;
  virtual B& operator=(const B& right) {x = right.x;return *this;}
};

struct D : public B {
  int y;
  // virtual D& operator=(const D& right) {x = right.x;
  //                                       y = right.y;return *this;}
  virtual B& operator=(const B& right) {x = right.x;
                     /* Default value*/ y = 13;return *this;}
};



int main(int argc, char** argv) {
  D d1;
  d1.x = 99;
  d1.y = 100;
  printf("d1.x d1.y %i %i\n", d1.x, d1.y);

  B& b1 = d1;
  D d2;
  B& b2 = d2;
  b2 = b1;
  printf("d2.x d2.y %i %i\n", d2.x, d2.y);
  return 0;
}