// https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
#include <iostream>

class C {
  std::size_t size_;
  int* array_;

 public:
  C(std::size_t size = 0)
      : size_(size), array_(size_ ? new int[size_] : nullptr) {}
  ~C() { delete[] array_; }
  C(C& other) {}
  C& operator=(C& other) {
    swap(*this, other);
    return *this;
  }
  friend void swap(C& a, C& b) {
    std::swap(a.size_, b.size_);    // non-throwing
    std::swap(a.array_, b.array_);  // non-throwing
  }
};