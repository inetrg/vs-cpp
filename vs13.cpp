#include <memory> // unique_ptr
#include <iostream> // cout

// "header"

class base {
public:
  base();
  virtual ~base();
  virtual void foo() = 0;
};

class derived : public base {
public:
  derived();
  ~derived();
  void foo() override;
};

// implementations

base::base() {
  std::cout << "base::base()\n";
}

base::~base() {
  std::cout << "base::~base()\n";
}

derived::derived() {
  std::cout << "derived::derived()\n";
}

derived::~derived() {
  std::cout << "derived::~derived()\n";
}

void derived::foo() {
  std::cout << "derived::foo()\n";
}

// main function

int main(int, char**) {
  std::unique_ptr<base> ptr{new derived};
  ptr->foo();
}
