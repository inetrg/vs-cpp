#include <iostream>
#include <string>

#include "caf/all.hpp"
#include "caf/io/all.hpp"

using namespace caf;

struct point2d;

CAF_BEGIN_TYPE_ID_BLOCK(vslab, first_custom_type_id)

// -- types ------------------------------------------------------------------

CAF_ADD_TYPE_ID(vslab, (point2d))

// -- atoms ------------------------------------------------------------------

CAF_ADD_ATOM(vslab, vs, add_atom)

CAF_END_TYPE_ID_BLOCK(vslab)

struct point2d {
  int x;
  int y;
};

template <class Inspector>
bool inspect(Inspector& f, point2d& p) {
  return f.object(p).fields(f.field("x", p.x), f.field("y", p.y));
}
behavior point_math() {
  return {
    [](add_atom, point2d p1, point2d p2) -> point2d {
      return point2d{p1.x + p2.x, p1.y + p2.y};
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
      .add(port, "port,p", "port for publish/remote_actor")
      .add(server, "server,s", "run as server");
  }
};

void caf_main(actor_system& sys, const config& cfg) {
  auto& mm = sys.middleman();
  if (cfg.server) {
    auto p = mm.publish(sys.spawn(point_math), cfg.port);
    if (!p)
      std::cerr << "unable to publish actor: " << to_string(p.error()) << '\n';
    else
      std::cout << "math actor published at port " << *p << '\n';
    return;
  }
  auto worker = mm.remote_actor(cfg.host, cfg.port);
  if (!worker) {
    std::cerr << "unable to connect to server: " << to_string(worker.error())
              << '\n';
    return;
  }
  scoped_actor self{sys};
  auto msg = make_message(vs::add_atom_v, point2d{10, 20}, point2d{15, 25});
  std::cout << to_string(msg) << " = ";
  self->request(*worker, infinite, msg)
    .receive([&](int result) { std::cout << result << '\n'; },
             [&](const error& err) { std::cout << to_string(err) << '\n'; });
}

CAF_MAIN(io::middleman, id_block::vslab)
