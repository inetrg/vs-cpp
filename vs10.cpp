#include <cassert>
#include <iostream>
#include <memory>
#include <tuple>
#include <utility>

// in .hpp file
class foo {
public:
  void bar();
};

// in .cpp file
void foo::bar() {
  std::cout << "foo::bar()\n";
}

int main(int, char**) {
  foo f;
  f.bar();
}
