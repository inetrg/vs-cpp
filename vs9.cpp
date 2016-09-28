#include <memory>
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

void f(int& x); // f can modify x
void g(const int& x); // x is immutable in g
void h(int* x); // h can modify content of x
void i(const int* x); // content of x is immutable in i

struct foo {
  void f1(); // might modify this object
  void f2() const; // this object is immutable in f2
};

void j(foo& x); // j can call f.f1() and f.f2()
void k(foo& x); // k can only call x.f2()

int main(int, char**) {
  // nop
}
