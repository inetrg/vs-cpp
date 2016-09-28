#include <memory>
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

int main(int, char**) {
  std::unique_ptr<int> xptr;
  assert(xptr == nullptr);
  xptr.reset(new int(10));
  assert(xptr != nullptr);
  cout << "x = " << *xptr << endl;
}
