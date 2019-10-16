#include <iostream>
#include <memory> // unique_ptr

std::ostream& operator<<(std::ostream& out, const std::unique_ptr<int>& x) {
  out << x.get();
  if (x)
    out << " (" << *x << ")";
  return out;
}

int main(int, char**) {
  std::unique_ptr<int> x;
  std::unique_ptr<int> y = std::make_unique<int>(42);
  auto print = [&] {
    std::cout << "x = " << x << ", "
              << "y = " << y << "\n";
  };
  print();
  // x = y => compiler error (unique_ptr is a move-only type)
  x = std::move(y); // ownership transfer
  print();
}
