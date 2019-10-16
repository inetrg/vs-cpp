#include <cassert>
#include <iostream>
#include <memory>
#include <tuple>
#include <utility>

struct point2d {
  int x;
  int y;
};

std::ostream& operator<<(std::ostream& out, const point2d& x) {
  return out << "point2d{" << x.x << ", " << x.y << "}";
}

int main(int, char**) {
  point2d p1{10, 20};
  std::cout << p1 << '\n';
}
