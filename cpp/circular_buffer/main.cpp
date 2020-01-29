#include <iostream>
#include "circular_buffer.hpp"

int main(void) {
  circular_buffer<unsigned long long int, 5> cb;
  cb.push_back(1);
  cb.push_back(2);
  cb.push_back(3);
  for (auto& value : cb) std::cout << value;
  std::cout << std::endl;
  cb.push_back(4);
  cb.push_back(5);
  cb.push_back(6);
  cb.push_back(6);
  for (auto& value : cb) std::cout << value;
  std::cout << std::endl;
}
