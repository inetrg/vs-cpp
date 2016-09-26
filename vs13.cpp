#include <string>
#include <iostream>

#include "caf/all.hpp"
#include "caf/io/all.hpp"

using namespace caf;

struct config : actor_system_config {
  std::string msg = "Hello world";
  config() {
    opt_group{custom_options_, "global"}.add(msg, "message,m", "set output");
  }
};

void caf_main(actor_system& sys, const config& cfg) {
  std::cout << cfg.msg << std::endl;
}

CAF_MAIN(io::middleman)
