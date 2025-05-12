#pragma once
#include "common.hpp"
#include "demonware/reply.hpp"

namespace demonware {
	class service_server {
	public:
		virtual ~service_server() = default;

		virtual std::shared_ptr<remote_reply> create_message(std::uint8_t type) {
			auto reply = std::make_shared<remote_reply>(this, type);
			return reply;
		}

		virtual std::shared_ptr<service_reply> create_reply(std::uint8_t type, std::uint32_t error = 0) {
			auto reply = std::make_shared<service_reply>(this, type, error, false);
			return reply;
		}

		virtual std::shared_ptr<structure_reply> create_structed_reply(std::uint8_t type) {
			auto reply = std::make_shared<structure_reply>(this, type);
			return reply;
		}

		virtual void send_reply(reply* data) = 0;
	};
}
