#include <bitset>
#include <iostream>
// clang-format off
int main() {
  std::bitset<4> bits{0b01'01};
  std::cout << bits << '\n';

  std::cout << (~bits) << " == 1010\n";
  std::cout << (bits|std::bitset<4>{0b00'11}) << " == 0111\n";
  std::cout << (bits&std::bitset<4>{0b00'11}) << " == 0001\n";
  std::cout << (bits^std::bitset<4>{0b00'11}) << " == 1001\n";
  std::cout << (bits&std::bitset<4>{0b00'10}) << " == 0010 testing bit\n";
  std::cout << (bits|std::bitset<4>{0b10'00}) << " == 1101 setting bit\n";

  return 0;
}