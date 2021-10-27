// clang-format off
#include <iostream>

class A {
  mutable int counter;
  int non_mutable;
  char a[10];

 public:
  A() : counter{0}, non_mutable{0} {}
  void f() { std::cout << "non const" << std::endl; }
  const char* operator[](unsigned int i) const {return &a[i];}
        char* operator[](unsigned int i)       {return &a[i];}
  void f() const {
    counter++;
    // non_mutable++; //нельзя!
    std::cout << "const, counter=" << counter << std::endl;
  }
};

void f(const int* b){
  *(const_cast<int*>(b))=777;
}

int main() {
  A a;
  const A& b = a;
  a.f();
  b.f();

  int c = 555;
  f(&c);
  std::cout << c << std::endl;
  const int cc = 555;
  f(&cc); // UB!
  std::cout << "UB" << cc << std::endl;

  //https://isocpp.org/wiki/faq/const-correctness#constptrptr-conversion
  //http://c-faq.com/ansi/constmismatch.html
  const char d = 'x';
  char *p1; //указатель на чар никуда не указывает пока
  //char const **p2 = &p1; //указатель на констатный указатель указывает туда же куда и p1 - никуда
  //*p2 = &d;  //дальше пытаемся через p1 изменить d
  //*p1 = 'X'; //нельзя!
  return 0;
}
