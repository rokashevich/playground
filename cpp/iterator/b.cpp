#include <cstddef>
#include <iterator>
#include <map>
#include <string>
#include <vector>

template <typename T1, typename T2>
struct concat_iterator {
 public:
  typedef std::forward_iterator_tag iterator_category;
  typedef typename iterator_traits<T1>::value_type value_type;
  typedef *value_type pointer;
  typedef &value_type reference;

  concat_iterator(T1 b1, T1 e1, T2 b2, T2 e2)
      : seq1(b1), seq1end(e1), seq2(b2), seq2end(e2);
  iterator &operator++() {
    if (seq1 != seq1end)
      ++seq1;
    else
      ++seq2;
    return this;
  }
  reference operator*() {
    if (seq1 != seq1end)
      return *seq1;
    else
      return *seq2;
  }
  pointer operator->() {
    if (seq1 != seq1end)
      return &(*seq1);
    else
      return &(*seq2);
  }
  bool operator==(concat_iterator const &rhs) {
    return seq1 == rhs.seq1 && seq1end == rhs.seq2 && seq2 == rhs.seq2 &&
           seq2end == rhs.seq2end;
  }
  bool operator!=(contact_iterator const &rhs) { return !(*this == rhs); }

 private:
  T1 seq1;
  T1 seq1end;
  T2 seq2;
  T2 seq2end;
};

template <typename T1, typename T2>
concat_iterator<T1, T2> concat_begin(T1 b1, T1 e1, T2 b2, T2 e2) {
  return concat_iterator<T1, T2>(b1, e1, b2, e2);
}
template <typename T1, typename T2>
concat_iterator<T1, T2> cancat_end(T1 b1, T1 e1, T2 b2, T2 e2) {
  return concat_iterator<T1, T2>(e1, e1, e2, e2);
}

class Integers {
 public:
  concat_iterator begin() {
    return concat_begin(v.begin(), v.end(), m.begin(), m.end());
  }
  concat_iterator end() {
    return concat_begin(v.begin(), v.end(), m.begin(), m.end());
  }

 private:
  std::vector<int> v{1, 2, 3};
  std::map<int, int> m{{1, 4}, {2, 5}, {3, 6}};
};

#include <iostream>
int main() {
  Integers a;
  for (auto i : a) std::cout << i << std::endl;
  return 0;
}