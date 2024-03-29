#include <cstddef>
#include <iterator>

class Integers {
 public:
  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer = int*;
    using reference = int&;

    Iterator(pointer ptr) : m_ptr(ptr) {}

    reference operator*() const { return *m_ptr; }
    pointer operator->() { return m_ptr; }
    Iterator& operator++() {
      m_ptr++;
      return *this;
    }
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    friend bool operator==(const Iterator& a, const Iterator& b) {
      return a.m_ptr == b.m_ptr;
    };
    friend bool operator!=(const Iterator& a, const Iterator& b) {
      return a.m_ptr != b.m_ptr;
    };

   private:
    pointer m_ptr;
  };

  Iterator begin() { return Iterator(&m_data[0]); }
  Iterator end() { return Iterator(&m_data[10]); }

 private:
  int m_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
};

#include <iostream>
int main() {
  Integers a;
  for (auto i : a) std::cout << i << std::endl;
  return 0;
}