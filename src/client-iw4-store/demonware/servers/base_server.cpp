#include "common.hpp"
#include "demonware/servers/base_server.hpp"

#include <utils/cryptography.hpp>
#include <utils/string.hpp>

namespace demonware {
	base_server::base_server(std::string name)
		: name_(std::move(name))
	{
		this->address_ = utils::cryptography::jenkins_one_at_a_time::compute(this->name_);
	}

	void base_server::debug_log_packet(const std::string& server_type, const std::string& packet) {
		LOG("Demonware/"s + server_type, DEBUG, "[{}]: received: {}", this->get_name(), utils::string::dump_hex(packet));
	}

	const std::string& base_server::get_name() const {
		return this->name_;
	}

	std::uint32_t base_server::get_address() const {
		return this->address_;
	}
}
