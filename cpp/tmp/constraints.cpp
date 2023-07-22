#include <vector>
template <class T1, class T2>
struct Can_copy {
  static void constraints(T1 a, T2 b) {
    T2 c = a;
    b = a;
  }
  Can_copy() { void (*p)(T1, T2) = constraints; }
};

template <class Container>
void print_all(Container& c) {
  typedef typename Container::value_type T;
  Can_copy<T, int>();
  // for_each(c.begin(), c.end(), mem_fun(&Shape::draw));
}

struct X {};

int main() {
  std::vector<int> i{1, 2, 3, 4, 5};
  std::vector<X> x{};
  print_all(i);
  print_all(x);
  return 0;
}