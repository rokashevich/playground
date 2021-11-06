// clang-format off
#include <cstdio>
struct Base {
  virtual ~Base(){};
  virtual Base *clone() const = 0;
  static Base *create(int id);
};

struct A : Base {
  A *clone() const {printf("A\n");return new A(*this);}
};

struct B : Base {
  B *clone() const {printf("A\n");return new B(*this);} 
};

Base *Base::create(int id) {
  if (id == 1) return new A; else return new B;
};

int main(){
  Base * p = Base::create(1);
  Base * q = p->clone();
}