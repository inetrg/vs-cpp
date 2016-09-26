#include <string>
#include <iostream>

#include "caf/all.hpp"
#include "caf/io/all.hpp"

using namespace caf;

behavior adder(event_based_actor* self) {
  return {
    [](int x, int y) {
      return x + y;
    }
  };
}

void caf_main(actor_system& sys) {
  scoped_actor self{sys};
  auto a = self->spawn(adder);
  self->request(a, infinite, 10, 20).receive(
    [&](int z) {
      aout(self) << "10 + 20 = " << z << std::endl;
    },
    [&](error& err) {
      aout(self) << "Error: " << sys.render(err) << std::endl;
    }
  );
}

CAF_MAIN(io::middleman)

