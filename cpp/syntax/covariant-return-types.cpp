// clang-format off
#include <iostream>
#include <cstdio>
struct B {
  virtual B* getThisBad()  { return this; }
  virtual B* getThisGood() { return this; }
};
struct D : public B {
  virtual B* getThisBad()  { printf("DBad\n");return this; }
  virtual D* getThisGood() { printf("DGood\n");return this; }
};
int main() {
  D d{};
  B& b{d};

  // D* d2 = d.getThisBad(); // error: invalid conversion from ‘B*’ to ‘D*’
  D* d2 = dynamic_cast<D*>(d.getThisBad());  // так ок
  D* d3 = d.getThisGood();                   // так еще проще!
  // ^^^ оба вызовут D через вирт. наследование

  // ВЕРНЁТ ТИП B!  Потому что возвращаемый функций
  // тип должен быть определён на этапе компиляции,
  // не рантайме (такова специфика языка).
  std::cout << typeid(b.getThisBad()).name();   // P1B
  std::cout << typeid(b.getThisGood()).name();  // P1B
  return 0;
}
