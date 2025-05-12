#pragma once
#include "common.hpp"
#include "demonware/reply.hpp"
#include "demonware/servers/tcp_server.hpp"

namespace demonware {
	class auth3_server : public tcp_server {
	public:
		using tcp_server::tcp_server;
	private:
		void send_reply(reply* data);
		void handle(const std::string& packet) override;
	};
}
