#pragma once
#include "common.hpp"
#include "demonware/servers/service_server.hpp"

#include <utils/string.hpp>

namespace demonware {
	class service {
		using callback_t = std::function<void(service_server*, byte_buffer*)>;

		std::uint8_t id_;
		std::string name_;
		std::mutex mutex_;
		std::uint8_t task_id_;
		std::map<std::uint8_t, callback_t> tasks_;
	public:
		virtual ~service() = default;
		service(service&&) = delete;
		service(const service&) = delete;
		service& operator=(const service&) = delete;

		service(const std::uint8_t id, std::string name)
			: id_(id)
			, name_(std::move(name))
			, task_id_(0)
		{}

		std::uint8_t id() const {
			return this->id_;
		}

		const std::string& name() const {
			return this->name_;
		}

		std::uint8_t task_id() const {
			return this->task_id_;
		}

		virtual void exec_task(service_server* server, const std::string& data) {
			std::lock_guard<std::mutex> _(this->mutex_);

			byte_buffer buffer(data);
			buffer.read_ubyte(&this->task_id_);

			const auto& it = this->tasks_.find(this->task_id_);

			if (it != this->tasks_.end()) {
				LOG("Demonware/Service", DEBUG, "[DW] {}: executing task '{:d}'", name_.data(), this->task_id_);
				it->second(server, &buffer);
			}
			else {
				LOG("Demonware/Service", DEBUG, "[DW] {}: missing task '{:d}'", name_.data(), this->task_id_);
				// return no error
				server->create_reply(this->task_id_)->send();
			}
		}
	protected:
		template <typename Class, typename T, typename... Args>
		void register_task(const std::uint8_t id, T (Class::* callback)(Args ...) const) {
			this->tasks_[id] = [this, callback](Args ... args) -> T {
				return (reinterpret_cast<Class*>(this)->*callback)(args...);
			};
		}

		template <typename Class, typename T, typename... Args>
		void register_task(const std::uint8_t id, T (Class::* callback)(Args ...)) {
			this->tasks_[id] = [this, callback](Args ... args) -> T {
				return (reinterpret_cast<Class*>(this)->*callback)(args...);
			};
		}
	};
}
