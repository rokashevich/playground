// clang-format off
#include <map>
#include <unordered_map>
#include <functional>
#include <cstddef> // size_t
struct S1 {
  char x;
  bool operator<(const S1& rhs) const { return x < rhs.x; }
};                           // ^^^^^ const важен!

class S2 {
public:
  char x; // нужен S(char) если x приватный
  friend struct Comparator; // нужно если х приватный
};
struct Comparator{
  bool operator()(const S2&lhs, const S2&rhs) const {
    return lhs.x < rhs.x;
  }
};

struct S3{
  char x,y;
  bool operator==(const S3& rhs) const {return x == rhs.x;}
};
struct Hash{
  size_t operator()(const S3& s){
    return (std::hash<char>{}(s.x))^(std::hash<char>{}(s.y));
  }       //^^^^^^^^^^^^^^^^^ функтор
};

int main() {
  S1 a{'a'};
  S1 b{'b'};
  std::map<S1,int> M{{a,1},{b,2}};
  
  S2 c{'c'};
  S2 d{'d'};
  std::map<S2, int, Comparator> M2{{c, 1}, {d, 2}};

  S3 e{'e','e'};
  S3 f{'f','f'};
  std::unordered_map<S3, int, Hash> M3{};
  return 0;
}