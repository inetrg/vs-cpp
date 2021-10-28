#include <iostream>
#include <string>

#include "caf/all.hpp"
#include "caf/io/all.hpp"

using namespace caf;

struct cell_state {
  int value = 0;
};

behavior cell(stateful_actor<cell_state>* self) {
  return {
    [=](get_atom) { return self->state.value; },
    [=](put_atom, int x) { self->state.value = x; },
  };
}

std::ostream& operator<<(std::ostream& out, const expected<message>& x) {
  return out << to_string(x);
}

void caf_main(actor_system& sys) {
  auto worker = sys.spawn(cell);
  scoped_actor self{sys};
  self->send(worker, put_atom_v, 42);
  self->request(worker, infinite, get_atom_v)
    .receive([&](int value) { std::cout << "cell value: " << value << '\n'; },
             [&](const error& err) {
               std::cerr << "unable to read cell: " << to_string(err) << '\n';
             });
}

CAF_MAIN(io::middleman)
