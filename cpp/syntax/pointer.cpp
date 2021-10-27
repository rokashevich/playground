// clang-format off
#include <iostream>

void f(int *&) {}

int main() {
  // int** array { new int[3][5] }; //нельзя!

  int (*array1)[5] { new int[2][5] };// эквиваленты, приоритет [] > *
  auto array2 { new int[3][5] };     // этот проще
  std::cout << typeid(int (*)[5]).name() << '\n'; // PA5_i
  std::cout << typeid(int (*)[]).name() << '\n';  // PA_i
  std::cout << typeid(int *[]).name() << '\n';    // A_Pi
  std::cout << typeid(int []).name() << '\n';     // A_i
  std::cout << typeid(int **).name() << '\n';     // PPi
  
  int** array3 { new int*[5] }; // array of 5 int pointers
  
  int** array10x5 { new int*[10] }; // allocate an array of 10 int pointers — these are our rows
  for (int count = 0; count < 10; ++count)
    array10x5[count] = new int[5]; // these are our columns

  int** array10xRANDOM { new int*[10] }; // allocate an array of 10 int pointers — these are our rows
  for (int count = 0; count < 10; ++count)
    array10xRANDOM[count] = new int[count+1]; // these are our columns

  if (0) {
    int i = 0;
    int j = 0;
    std::cout << ++i + ++j << '\n';  //=2|Приоритеты: ++x,--x=3;
    std::cout << i++ + j++ << '\n';  //=2|x++,x--=2;*/=5,+/-=6, <</>>=7
    // std::cout << ++i++ << '\n';  // error: lvalue required as increment
    // operand std::cout << ++(i++) << '\n'; // тоже самое
    std::cout << (++i)++ << '\n';  // 3

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
