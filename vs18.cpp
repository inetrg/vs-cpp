#include <string>
#include <iostream>

#include "caf/all.hpp"
#include "caf/io/all.hpp"

using std::cout;
using std::cerr;
using namespace caf;

using add_atom = atom_constant<atom("add")>;

struct point2d {
  int x;
  int y;
};

template <class Inspector>
typename Inspector::result_type inspect(Inspector& f, point2d& p) {
  return f(meta::type_name("point2d"), p.x, p.y);
}
behavior point_math() {
  return {
    [](add_atom, point2d p1, point2d p2) -> point2d {
      return point2d{p1.x + p2.x, p1.y + p2.y};
    }
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
    add_message_type<point2d>("point2d");
    opt_group{custom_options_, "global"}
    .add(host, "host,H", "hostname of server")
    .add(port, "port,p", "port for publish/remote_actor")
    .add(server, "server,s", "run as server");
  }
};

void caf_main(actor_system& sys, const config& cfg) {
  auto& mm = sys.middleman();
  if (cfg.server) {
    auto p = mm.publish(sys.spawn(point_math), cfg.port);
    if (!p)
      cerr << "unable to publish actor: " << sys.render(p.error()) << "\n";
    else
      cout << "math actor published at port " << *p << "\n";
  } else {
    auto x = mm.remote_actor(cfg.host, cfg.port);
    if (!x)
      cerr << "unable to connect to server: " << sys.render(x.error()) << "\n";
    else {
      auto f = make_function_view(*x);
      point2d p1{10, 20};
      point2d p2{15, 25};
      cout << "f('add', p1, p2) = " << f(add_atom::value, p1, p2) << "\n";
    }
  }
}

CAF_MAIN(io::middleman)

