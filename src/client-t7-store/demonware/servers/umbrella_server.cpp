#include "common.hpp"
#include "demonware/servers/umbrella_server.hpp"

#include <utils/string.hpp>

namespace demonware {
	void umbrella_server::handle(const std::string& packet) {
		// TODO: Implement
		LOG("Demonware/UmbrellaServer", DEBUG, "called handle: {}", utils::string::dump_hex(packet));
	}
}
