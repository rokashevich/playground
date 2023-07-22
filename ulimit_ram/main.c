#include <stdlib.h>
#include <unistd.h>
int main() {
  long int size = 100000000;  // 100MB in bytes
  char *ptr;

  ptr = malloc(size);
  ptr = malloc(size);

  while (1) {
    sleep(1);
  }

  return 0;
}
