#pragma once
#include "common.hpp"
#include "demonware/servers/tcp_server.hpp"

namespace demonware {
	class umbrella_server : public tcp_server {
	public:
		using tcp_server::tcp_server;
	private:
		void handle(const std::string& packet) override;
	};
}
