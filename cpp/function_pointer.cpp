#include <iostream>
// clang-format off

int DoC(float a, char b){ printf("DoC\n"); return a+b; }

struct TMyClass {
  int DoInstance(float a, char b) { printf("DoInstance\n"); return a + b; }
  static int DoStatic(float a, char b) {printf("DoStatic\n");return a + b;}
};

struct Functor{
  int operator()(float a, char b){printf("Functor\n"); return a + b; }
};

// Функция, принимающая double и возвращающая функцию
// принимающую float и char и возвращающую int.
int (*GetP1(double d))(float, char) {return &DoC;}
// Альтернативный вариант
typedef int(*p2f)(float, char);
p2f GetP2(double d) {return &DoC;}
// Самый простой вариант!
auto GetP3(double d) {return &DoC;} 

int main(){
  int (*pcf)(float, char);
  pcf = DoC;  // short form
  pcf = &DoC; // correct assignment using address operator
  pcf(1,2);
  (*pcf)(1,2);

  pcf = &TMyClass::DoStatic; // можно переиспользовать pcf
  pcf(1,2);

  int (TMyClass::*imember)(float, char);
  imember = &TMyClass::DoInstance; // нельзя pcf
  TMyClass i1;
  (i1.*imember)(1, 2);   
  
  GetP1(1.0)(1,2);
  GetP2(1.0)(1,2);
  GetP3(1.0)(1,2);

  // Массив указателей
  typedef int(*tpcf)(float,char);
  tpcf pcf_arr[10];
  pcf_arr[0] = &DoC;
  pcf_arr[0](1,2);

  // Функтор
  Functor f;
  f(1,2);
 
  return 0;
}