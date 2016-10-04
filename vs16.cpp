#include <string>
#include <iostream>

#include "caf/all.hpp"
#include "caf/io/all.hpp"

using std::cout;
using namespace caf;

using add_atom = atom_constant<atom("add")>;
using sub_atom = atom_constant<atom("sub")>;
using mul_atom = atom_constant<atom("mul")>;
using div_atom = atom_constant<atom("div")>;

behavior math() {
  return {
    [](add_atom, int x, int y) {
      return x + y;
    },
    [](sub_atom, int x, int y) {
      return x - y;
    },
    [](mul_atom, int x, int y) {
      return x * y;
    },
    [](div_atom, int x, int y) -> result<int> {
      if (y == 0)
        return sec::invalid_argument;
      return x / y;
    }
  };
}

std::ostream& operator<<(std::ostream& out, const expected<message>& x) {
  return out << to_string(x);
}

void caf_main(actor_system& sys) {
  auto f = make_function_view(sys.spawn(math));
  cout << "f('add', 4, 2) = " << f(add_atom::value, 4, 2) << "\n"
       << "f('sub', 4, 2) = " << f(sub_atom::value, 4, 2) << "\n"
       << "f('mul', 4, 2) = " << f(mul_atom::value, 4, 2) << "\n"
       << "f('div', 4, 2) = " << f(div_atom::value, 4, 2) << "\n"
       << "f('div', 1, 0) = " << f(div_atom::value, 1, 0) << "\n";
}

CAF_MAIN(io::middleman)
