#include <memory>
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

int main(int, char**) {
  int x = 5;
  int& xref = x;
  int* xptr = &x;
  xref = 10;
  int& xref2 = *xptr;
  xref2 = 20;
  cout << "x = " << x << endl;
}
