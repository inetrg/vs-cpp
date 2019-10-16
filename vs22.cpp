#include <iostream>
#include <stdexcept>
#include <string>

#include "caf/all.hpp"
#include "caf/io/all.hpp"

using namespace caf;

using add_atom = atom_constant<atom("add")>;

behavior writer(event_based_actor* self, const actor& user) {
  return {
    [=](const std::string& line) {
      if (self->current_sender() != user)
        std::cout << line << '\n';
    },
    [=](const group_down_msg&) {
      std::cerr << "FATAL: server is down!\nPress ENTER to exit.\n";
      fclose(stdin);
    },
  };
}

struct config : actor_system_config {
  config() {
    opt_group{custom_options_, "global"}
      .add(is_server, "server,s", "run in server mode")
      .add(port, "port,p",
           "set port for publishing of / connecting to chatrooms")
      .add(host, "host,H", "hostname or IP of the chat server")
      .add(room, "room,r", "name of the chatroom")
      .add(name, "name,n", "username in chat");
  }

  bool is_server = false;
  uint16_t port = 0;
  std::string host = "localhost";
  std::string room = "vslab";
  std::string name = "vslab-student";
};

void caf_main(actor_system& sys, const config& cfg) {
  if (cfg.is_server) {
    if (auto port = sys.middleman().publish_local_groups(cfg.port)) {
      std::cout << ">> running at port " << *port << '\n'
                << ">> press ENTER to stop the server\n";
      getc(stdin);
    } else {
      std::cout << ">> publishing failed: " << sys.render(port.error()) << '\n';
    }
    return;
  }
  group grp;
  std::cout << ">> try to join room " << cfg.room << " on " << cfg.host
            << " at port " << cfg.port << " ...\n";
  if (auto rg = sys.middleman().remote_group(cfg.room, cfg.host, cfg.port)) {
    grp = std::move(*rg);
    std::cout << ">> got group: " << to_string(grp) << '\n';
  } else {
    std::cerr << ">> failed to get group: " << sys.render(rg.error()) << '\n';
    return;
  }
  scoped_actor self{sys};
  auto worker = self->spawn_in_group(grp, writer, self);
  std::string prefix = cfg.name + ": ";
  std::string line;
  while (std::getline(std::cin, line)) {
    line.insert(line.begin(), prefix.begin(), prefix.end());
    self->send(grp, line);
  }
  self->send_exit(worker, exit_reason::user_shutdown);
}

CAF_MAIN(io::middleman)
