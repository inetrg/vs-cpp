#include <cassert>
#include <iostream>
#include <memory>

int main(int, char**) {
  std::unique_ptr<int> xptr;
  assert(xptr == nullptr);
  xptr = std::make_unique<int>(10);
  assert(xptr != nullptr);
  std::cout << "x = " << *xptr << '\n';
}
