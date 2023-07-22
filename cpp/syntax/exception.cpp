#include <exception>
#include <iostream>

struct bomb_exception : public std::exception {};
struct main_exception : public std::exception {};

struct Bomb {
  ~Bomb() {
    try {
      throw bomb_exception();
    } catch (std::exception) {
      throw;
    }
    // std::cout << "Bomb dtor" << std::endl;
  }
};
int main() {
  try {
    Bomb bomb;
    throw main_exception();
  } catch (const std::exception&) {
    std::cout << "std::exception" << std::endl;
  } catch (main_exception&) {
    std::cout << "main_exception" << std::endl;
  } catch (bomb_exception&) {
    std::cout << "bomb_exception" << std::endl;
  }
}
