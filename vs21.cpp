#include <string>
#include <iostream>
#include <stdexcept>

#include "caf/all.hpp"
#include "caf/io/all.hpp"

using std::cout;
using namespace caf;

using add_atom = atom_constant<atom("add")>;

behavior unreliable_worker(event_based_actor* self) {
  return {
    [=](add_atom, int x, int y) -> result<int> {
      if (x % 2 == 1 || y % 2 == 1) {
        self->quit(sec::invalid_argument);
        return make_error(sec::invalid_argument,
                          "I don't do odd numbers!");
      }
      return x + y;
    }
  };
}

struct state {
  actor worker;
};

behavior adder(stateful_actor<state>* self) {
  self->state.worker = self->spawn(unreliable_worker);
  self->link_to(self->state.worker);
  self->set_exit_handler([=](const exit_msg& dm) {
    if (dm.source == self->state.worker) {
      cout << "<<<restart failed worker>>>\n";
      // <linked> is a shortcut for calling link_to() afterwards
      self->state.worker = self->spawn<linked>(unreliable_worker);
    }
  });
  return {
    [=](add_atom a, int x, int y) {
      return self->delegate(self->state.worker, a, x, y);
    }
  };
}

std::ostream& operator<<(std::ostream& out, const expected<message>& x) {
  return out << to_string(x);
}

void caf_main(actor_system& sys) {
  auto f = make_function_view(sys.spawn(adder));
  cout << "10 + 20 = " << f(add_atom::value, 10, 20) << "\n"
       << "11 + 20 = " << f(add_atom::value, 11, 20) << "\n"
       << "2 + 4 = " << f(add_atom::value, 2, 4) << "\n";
}

CAF_MAIN(io::middleman)

