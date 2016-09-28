#include <tuple>
#include <memory>
#include <utility>
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

// in .hpp file
class foo {
public:
  void bar();
};

// in .cpp file
void foo::bar() {
  cout << "foo::bar()\n";
}

int main(int, char**) {
  foo f;
  f.bar();
}
