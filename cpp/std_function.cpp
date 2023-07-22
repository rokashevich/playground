#include <functional>
#include <iostream>

// void invoke(const std::function<void()>& fn) { fn(); }
void invoke(void (*fn)()) { fn(); }

int main() {
  int i{0};

  // Increments and prints its local copy of @i.
  // auto count{[&i]() mutable { std::cout << ++i << '\n'; }};
  auto count_capturing{[&i]() { std::cout << ++i << '\n'; }};
  auto count_no_captur{[]() { std::cout << "no" << '\n'; }};

  invoke(static_cast<void (*)()>(count_no_captur));
  // invoke(count);
  // invoke(count);

  return 0;
}