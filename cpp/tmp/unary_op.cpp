#include <algorithm>
#include <iostream>
#include <vector>
template <typename T>
struct DereferencedEqual {
  DereferencedEqual(T p) : p_(p) {}
  bool operator()(T p2) { return p_ == p2; }

 private:
  T p_;
};

struct Fred {
  Fred(int x) : i(x) {}
  bool operator==(Fred& r) { return i == r.i; }
  int i;
};

int main() {
  std::vector<Fred> v{1, 2, 3};
  auto pos = std::find_if(v.begin(), v.end(), DereferencedEqual<Fred>(v.at(1)));
  std::cout << (*pos).i << std::endl;
  return 0;
}
