#include <iostream>

int main(int, char**) {
  int x = 5;
  int* xptr = &x;
  *xptr = 10;
  std::cout << "x = " << x << '\n';
}
