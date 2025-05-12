#pragma once
#include "common.hpp"
#include "demonware/servers/base_server.hpp"

#include <utils/concurrency.hpp>

namespace demonware {
	class udp_server : public base_server {
	public:
		struct endpoint_data {
			SOCKET socket_{};
			sockaddr_in address_{};

			endpoint_data() = default;

			endpoint_data(const SOCKET sock, const sockaddr* addr, const int size) {
				if (size != sizeof(this->address_)) {
					throw std::runtime_error("Invalid size");
				}

				this->socket_ = sock;
				std::memcpy(&this->address_, addr, sizeof(this->address_));
			}
		};

		using base_server::base_server;

		void handle_input(const char* buf, std::size_t size, endpoint_data endpoint);
		std::size_t handle_output(SOCKET socket, char* buf, std::size_t size, sockaddr* address, int* addrlen);
		bool pending_data(SOCKET socket);

		void frame() override;
	protected:
		void send(const endpoint_data& endpoint, std::string data);

		virtual void handle(const endpoint_data& endpoint, const std::string& data) = 0;
	private:
		struct in_packet {
			std::string data_;
			endpoint_data endpoint_;
		};

		struct out_packet {
			std::string data_;
			sockaddr_in address_;
		};

		using in_queue = std::queue<in_packet>;
		using out_queue = std::queue<out_packet>;
		using socket_queue_map = std::unordered_map<SOCKET, out_queue>;

		utils::concurrency::container<in_queue> in_queue_;
		utils::concurrency::container<socket_queue_map> out_queue_;
	};
}
