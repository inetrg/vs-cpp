#include <memory> // unique_ptr
#include <iostream>

using std::cout;
using std::unique_ptr;

std::ostream& operator<<(std::ostream& out, const unique_ptr<int>& x) {
  out << x.get();
  if (x)
    out << " (" << *x << ")";
  return out;
}

int main(int, char**) {
  unique_ptr<int> x;
  unique_ptr<int> y{new int(42)};
  auto print = [&] {
    cout << "x = " << x << ", "
         << "y = " << y << "\n";
  };
  print();
  // x = y => compiler error (unique_ptr is a move-only type)
  x = std::move(y); // ownership transfer
  print();
}
