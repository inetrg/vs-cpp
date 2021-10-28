#include <iostream>
#include <string>

#include "caf/all.hpp"
#include "caf/io/all.hpp"

using namespace caf;

CAF_BEGIN_TYPE_ID_BLOCK(vslab, first_custom_type_id)

CAF_ADD_ATOM(vslab, vs, add_atom)
CAF_ADD_ATOM(vslab, vs, sub_atom)
CAF_ADD_ATOM(vslab, vs, mul_atom)
CAF_ADD_ATOM(vslab, vs, div_atom)

CAF_END_TYPE_ID_BLOCK(vslab)

behavior math() {
  return {
    [](vs::add_atom, int x, int y) { return x + y; },
    [](vs::sub_atom, int x, int y) { return x - y; },
    [](vs::mul_atom, int x, int y) { return x * y; },
    [](vs::div_atom, int x, int y) -> result<int> {
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
  for (auto msg :
       {make_message(vs::add_atom_v, 4, 2), make_message(vs::sub_atom_v, 4, 2),
        make_message(vs::mul_atom_v, 4, 2), make_message(vs::div_atom_v, 4, 2),
        make_message(vs::div_atom_v, 1, 0)}) {
    std::cout << to_string(msg) << " = ";
    self->request(worker, infinite, msg)
      .receive([&](int z) { std::cout << std::to_string(z) << '\n'; },
               [&](const error& err) { std::cout << to_string(err) << '\n'; });
  }
}

CAF_MAIN(io::middleman, id_block::vslab)
