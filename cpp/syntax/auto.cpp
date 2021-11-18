#include <iostream>
int main() {
  const int& a = 1;
  std::cout << typeid(decltype(a)).name() << std::endl;

  // auto a = {1, 2, 3};
  // std::cout << typeid(a).name() << std::endl;
  // auto&& uref3 = 27;
  // int&& uref4 = 27;
  // std::cout << typeid(uref3).name() << std::endl;
  // std::cout << typeid(uref4).name() << std::endl;

  // const char nam[] = "hello";
  // const char* name = "heelo";
  // auto usl = name;
  // auto& ref = name;
  // auto&& uni = name;
  // std::cout << sizeof(nam) << " " << sizeof(nam[0]) << std::endl;
  // std::cout << sizeof(name) << " " << sizeof(name[0]) << std::endl;
  // std::cout << sizeof(int) << std::endl;
  // std::cout << typeid(name).name() << std::endl;
  // std::cout << typeid(usl).name() << std::endl;
  // std::cout << typeid(ref).name() << std::endl;
  // std::cout << typeid(uni).name() << std::endl;

  return 0;
}