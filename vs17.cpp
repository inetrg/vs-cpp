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
      std::cerr << "unable to publish actor: " << sys.render(p.error()) << '\n';
    else
      std::cout << "math actor published at port " << *p << '\n';
  } else {
    auto adder = mm.remote_actor(cfg.host, cfg.port);
    if (!adder) {
      std::cerr << "unable to connect to server: " << sys.render(adder.error())
                << '\n';
    } else {
      scoped_actor self{sys};
      for (auto msg : {make_message(add_atom::value, 4, 2),
                       make_message(sub_atom::value, 4, 2),
                       make_message(mul_atom::value, 4, 2),
                       make_message(div_atom::value, 4, 2),
                       make_message(div_atom::value, 1, 0)}) {
        std::cout << to_string(msg) << " = ";
        self->request(*adder, infinite, msg)
          .receive([&](int result) { std::cout << result << '\n'; },
                   [&](const error& err) {
                     std::cout << sys.render(err) << '\n';
                   });
      };
    }
  }
}

CAF_MAIN(io::middleman)
