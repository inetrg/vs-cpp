#include <iostream>
#include <string>

#include "caf/all.hpp"
#include "caf/io/all.hpp"

using std::cout;
using namespace caf;

behavior adder(event_based_actor* self) {
  return {
    [](int x, int y) { return x + y; },
  };
}

void caf_main(actor_system& sys) {
  actor a = sys.spawn(adder);
  // scoped actor for ad hoc communication
  scoped_actor self{sys};
  self->request(a, infinite, 1, 2)
    .receive([&](int z) { cout << "1 + 2 = " << z << "\n"; },
             [&](error& err) { cout << "Error: " << sys.render(err) << "\n"; });
}

CAF_MAIN(io::middleman)
