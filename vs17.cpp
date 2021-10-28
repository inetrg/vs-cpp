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

struct config : actor_system_config {
  std::string host = "localhost";
  uint16_t port = 0;
  bool server = false;
  config() {
    opt_group{custom_options_, "global"}
      .add(host, "host,H", "hostname of server")
      .add(port, "port,p", "IP port for publish/remote_actor")
      .add(server, "server,s", "run as server");
  }
};

void caf_main(actor_system& sys, const config& cfg) {
  auto& mm = sys.middleman();
  if (cfg.server) {
    auto p = mm.publish(sys.spawn(math), cfg.port);
    if (!p)
      std::cerr << "unable to publish actor: " << to_string(p.error()) << '\n';
    else
      std::cout << "math actor published at port " << *p << '\n';
  } else {
    auto adder = mm.remote_actor(cfg.host, cfg.port);
    if (!adder) {
      std::cerr << "unable to connect to server: " << to_string(adder.error())
                << '\n';
    } else {
      scoped_actor self{sys};
      for (auto msg : {make_message(vs::add_atom_v, 4, 2),
                       make_message(vs::sub_atom_v, 4, 2),
                       make_message(vs::mul_atom_v, 4, 2),
                       make_message(vs::div_atom_v, 4, 2),
                       make_message(vs::div_atom_v, 1, 0)}) {
        std::cout << to_string(msg) << " = ";
        self->request(*adder, infinite, msg)
          .receive([&](int result) { std::cout << result << '\n'; },
                   [&](const error& err) {
                     std::cout << to_string(err) << '\n';
                   });
      };
    }
  }
}

CAF_MAIN(io::middleman, id_block::vslab)
