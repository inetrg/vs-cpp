#include <memory>
#include <iostream>

using std::cout;
using std::endl;

int main(int, char**) {
  int x = 5;
  int* xptr = &x;
  *xptr = 10;
  cout << "x = " << x << endl;
}
