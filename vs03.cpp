#include <iostream>

class scoped {
public:
  scoped() {
    std::cout << "scoped()\n";
  }
  ~scoped() {
    std::cout << "~scoped()\n";
  }
};

int main(int, char**) {
  std::cout << "enter main function\n";
  scoped x;
  std::cout << "leave main function\n";
}
