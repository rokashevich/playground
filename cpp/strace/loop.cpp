#include <unistd.h>

#include <iostream>

int main() {
  while (1) {
    std::cout << "Sleep 1 second" << std::endl;
    sleep(1);
  }
  return 0;
}
