#include <string>
#include <iostream>

#include "caf/all.hpp"
#include "caf/io/all.hpp"

using std::cout;
using namespace caf;

using add_atm = atom_constant<atom("add")>;
using sub_atm = atom_constant<atom("sub")>;
using mul_atm = atom_constant<atom("mul")>;
using div_atm = atom_constant<atom("div")>;

behavior math() {
  return {
    [](add_atm, int x, int y) {
      return x + y;
    },
    [](sub_atm, int x, int y) {
      return x - y;
    },
    [](mul_atm, int x, int y) {
      return x * y;
    },
    [](div_atm, int x, int y) -> result<int> {
      if (y == 0)
        return sec::invalid_argument;
      return x / y;
    }
  };
}

void caf_main(actor_system& sys) {
  actor a = sys.spawn(adder);
  auto f = make_function_view(a);
  cout << "f(1, 2) = " << f(1, 2) << endl;
  scoped_actor self{sys};
  self->request(a, infinite, 1, 2).receive(
    [&](int z) {
      cout << "1 + 2 = " << z << "\n";
    },
    [&](error& err) {
      cout << "Error: " << sys.render(err) << "\n";
    }
  );
}

CAF_MAIN(io::middleman)
