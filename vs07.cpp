#include <cassert>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;

int main(int, char**) {
  int x = 5;
  int& xref = x;
  int* xptr = &xref;
  xref = 10;
  int& xref2 = *xptr;
  xref2 = 20;
  std::cout << "x = " << x << '\n';
}
