#pragma once
#include "common.hpp"

namespace demonware {
	class base_server {
	public:
		using stream_queue = std::queue<char>;
		using data_queue = std::queue<std::string>;

		base_server(std::string name);

		base_server(base_server&&) = delete;
		base_server(const base_server&) = delete;
		base_server& operator=(base_server&&) = delete;
		base_server& operator=(const base_server&) = delete;

		virtual ~base_server() = default;

		void debug_log_packet(const std::string& server_type, const std::string& packet);
		const std::string& get_name() const;
		std::uint32_t get_address() const;

		virtual void frame() = 0;
	private:
		std::string name_;
		std::uint32_t address_ = 0;
	};
}
