#include <initializer_list>
#include <map>
#include <vector>
template <typename T>
void f(T) {}
int main() {
  f<std::initializer_list<int>>({1, 2, 3, 4, 5});
  std::vector<int> b{5, 4, 3, 2, 1};
  f(b);
  // f({1, 2, 3, 4, 5});//couldn’t deduce template parameter ‘T’
  std::map<int, std::vector<int>> c{{1, {1, 1}}, {2, {2, 2}}};
  f(c);
  return 0;
}