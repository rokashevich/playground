// clang-format off
#include <iostream>
struct B {
  virtual B* getThisBad()      { return this; }
  virtual B* getThisGood()      { return this; }
};
struct D : public B {
  virtual B* getThisBad()      { return this; }
  virtual D* getThisGood()      { return this; }
};
int main() {
  D d{};
  B& b{d};

  // D* d2 = d.getThisBad(); // error: invalid conversion from ‘B*’ to ‘D*’
  D* d2 = dynamic_cast<D*>(d.getThisBad()); // так ок
  D* d3 = d.getThisGood();                  // так еще проще!

  // ВЕРНЁТ ТИП B!  Потому что возвращаемый функций 
  // тип должен быть определён на этапе компиляции, 
  // не рантайме (такова специфика языка). 
  std::cout << typeid(b.getThisGood()).name();
  return 0;
}
