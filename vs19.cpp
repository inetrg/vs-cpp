#include <string>
#include <iostream>

#include "caf/all.hpp"
#include "caf/io/all.hpp"

using std::cout;
using namespace caf;

struct cell_state {
  int value = 0;
};

behavior cell(stateful_actor<cell_state>* self) {
  return {
    [=](get_atom) {
      return self->state.value;
    },
    [=](put_atom, int x) {
      self->state.value = x;
    }
  };
}

std::ostream& operator<<(std::ostream& out, const expected<message>& x) {
  return out << to_string(x);
}

void caf_main(actor_system& sys) {
  auto f = make_function_view(sys.spawn(cell));
  f(put_atom::value, 42);
  cout << "cell value: " << f(get_atom::value) << "\n";
}

CAF_MAIN(io::middleman)

