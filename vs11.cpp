#include <tuple>
#include <memory>
#include <utility>
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

struct point2d { int x; int y; };

std::ostream& operator<<(std::ostream& out, const point2d& x) {
  return out << "point2d{" << x.x << ", " << x.y << "}";
}

int main(int, char**) {
  point2d p1{10, 20};
  cout << p1 << endl;
}
