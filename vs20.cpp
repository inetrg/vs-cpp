#include <iostream>
#include <stdexcept>
#include <string>

#include "caf/all.hpp"
#include "caf/io/all.hpp"

using namespace caf;

using add_atom = atom_constant<atom("add")>;

behavior unreliable_worker(event_based_actor* self) {
  return {
    [=](add_atom, int x, int y) -> result<int> {
      if (x % 2 == 1 || y % 2 == 1) {
        self->quit(sec::invalid_argument);
        return make_error(sec::invalid_argument, "I don't do odd numbers!");
      }
      return x + y;
    },
  };
}

struct state {
  actor worker;
};

behavior adder(stateful_actor<state>* self) {
  self->state.worker = self->spawn(unreliable_worker);
  self->monitor(self->state.worker);
  self->set_down_handler([=](const down_msg& dm) {
    if (dm.source == self->state.worker) {
      std::cout << "<<<restart failed worker>>>\n";
      // <monitored> is a shortcut for calling monitor() afterwards
      self->state.worker = self->spawn<monitored>(unreliable_worker);
    }
  });
  return {
    [=](add_atom a, int x, int y) {
      return self->delegate(self->state.worker, a, x, y);
    },
  };
}

void caf_main(actor_system& sys) {
  auto worker = sys.spawn(adder);
  scoped_actor self{sys};
  for (auto msg : {make_message(add_atom::value, 10, 20),
                   make_message(add_atom::value, 11, 20),
                   make_message(add_atom::value, 2, 4)}) {
    std::cout << to_string(msg) << " = ";
    self->request(worker, infinite, msg)
      .receive([&](int result) { std::cout << result << '\n'; },
               [&](const error& err) { std::cout << sys.render(err) << '\n'; });
  }
}

CAF_MAIN(io::middleman)
