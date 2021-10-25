#include <iostream>

void f(int *&) {}

int main() {
  int i = 0;
  int j = 0;
  std::cout << ++i + ++j << '\n';  // 2|Приоритеты: ++x,--x=2;
  std::cout << i++ + j++ << '\n';  // 2|x++,x--=3;*/=5,+/-=6, <</>>=7
  // std::cout << ++i++ << '\n';  // error: lvalue required as increment operand
  // std::cout << ++(i++) << '\n'; // тоже самое
  std::cout << (++i)++ << '\n';  // 3

  if (0) {
    // warning: ISO C++ forbids converting a string constant to ‘char*’
    // char *label{"xxxx"}; // BAD
    const char *label{"xxxx"};
    // label[1] = 'y'; // Так соотвественно нельзя т.к. const

    std::cout << std::string(label) << '\n';

    // int *p;
    // f(p);
    // std::cout << *p << '\n';

    char ar_char[] = {'a', 'b', 'c'};
    short ar_short[] = {1, 2, 3};
    int ar_int[] = {1, 2, 3};
    long ar_long[] = {1, 2, 3};
    long long ar_long_long[] = {1, 2, 3};
    std::cout << "ar_char      " << sizeof(ar_char) << std::endl;
    std::cout << "ar_short     " << sizeof(ar_short) << std::endl;
    std::cout << "ar_int       " << sizeof(ar_int) << std::endl;
    std::cout << "ar_long      " << sizeof(ar_long) << std::endl;
    std::cout << "ar_long_long " << sizeof(ar_long_long) << std::endl;
  }
  return 0;
}
