#include <functional>
#include <iostream>
#include <numeric>
struct S {  // take something you can call using ()
  float operator()(int x, int y) const { return ((float)x) / y; };
  float sum(int x, int y) const { return x + y; };
};
int main() {
  std::function<float(int x, int y)> f;  // make a function object

  f = S{};                            // assign
  std::cout << f(5, 3) << std::endl;  // call through the function object
  std::cout << S{}(5, 3) << std::endl;

  typedef float (S::*F)(int, int) const;
  F pf = &S::sum;
  F pff = &S::operator();
  std::cout << std::invoke(pff, S{}, 1, 2) << '\n';
  std::cout << (S{}.*pff)(2, 3) << '\n';

  using PFFF = float (S::*)(int, int) const;
  PFFF pfff = &S::operator();
  std::cout << (S{}.*pfff)(3, 4) << '\n';

  // std::accumulate(b, e, 1, f);        // passes beautifully
}
