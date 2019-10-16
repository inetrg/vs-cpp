#include <iostream>
#include <string>

#include "caf/all.hpp"
#include "caf/io/all.hpp"

using namespace caf;

using add_atom = atom_constant<atom("add")>;
using sub_atom = atom_constant<atom("sub")>;
using mul_atom = atom_constant<atom("mul")>;
using div_atom = atom_constant<atom("div")>;

behavior math() {
  return {
    [](add_atom, int x, int y) { return x + y; },
    [](sub_atom, int x, int y) { return x - y; },
    [](mul_atom, int x, int y) { return x * y; },
    [](div_atom, int x, int y) -> result<int> {
      if (y == 0)
        return sec::invalid_argument;
      return x / y;
    },
  };
}

std::ostream& operator<<(std::ostream& out, const expected<message>& x) {
  return out << to_string(x);
}

void caf_main(actor_system& sys) {
  scoped_actor self{sys};
  auto worker = sys.spawn(math);
  for (auto msg : {make_message(add_atom::value, 4, 2),
                   make_message(sub_atom::value, 4, 2),
                   make_message(mul_atom::value, 4, 2),
                   make_message(div_atom::value, 4, 2),
                   make_message(div_atom::value, 1, 0)}) {
    std::cout << to_string(msg) << " = ";
    self->request(worker, infinite, msg)
      .receive([&](int z) { std::cout << std::to_string(z) << '\n'; },
               [&](const error& err) { std::cout << sys.render(err) << '\n'; });
  }
}

CAF_MAIN(io::middleman)
