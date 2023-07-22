// clang-format off
// https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
#include <iostream>
#include <algorithm>
class C {
  std::size_t size_;
  int* array_;

 public:
  C(std::size_t size = 0) //default constructor
      : size_{size}, array_{size_ ? new int[size_] : nullptr} {}
  C(const C& other) //copy-constructor
      : size_{other.size_}, array_{size_?new int[size_] : nullptr} {
    std::copy(other.array_, other.array_ + size_, array_);
  }
  C(C&& other) noexcept //move-constructor
      : C() {
    swap(*this, other);
  }
  ~C() { delete[] array_; } //destructor
  C& operator=(C other) {
    swap(*this, other);
    return *this;
  }
  friend void swap(C& a, C& b) {
    std::swap(a.size_, b.size_);    // non-throwing
    std::swap(a.array_, b.array_);  // non-throwing
  }
};

int main(){return 0;}