void segfault() {
  int c = 3;
  int *ptr = nullptr;
  *ptr = 42;
}

int main() {
  int a = 1;
  int b = 2;
  segfault();
  return 0;
}
