#pragma once
#include "common.hpp"
#include "demonware/bit_buffer.hpp"
#include "demonware/byte_buffer.hpp"
#include "demonware/data_types.hpp"

namespace demonware {
	class reply {
	public:
		reply() = default;

		reply(reply&&) = delete;
		reply(const reply&) = delete;
		reply& operator=(reply&&) = delete;
		reply& operator=(const reply&) = delete;

		virtual ~reply() = default;
		virtual std::string data() = 0;
	};

	class raw_reply : public reply {
	public:
		raw_reply() = default;

		explicit raw_reply(std::string data)
			: buffer_(std::move(data))
		{}

		std::string data() override {
			return this->buffer_;
		}
	protected:
		std::string buffer_;
	};

	class typed_reply : public raw_reply {
	public:
		typed_reply(const std::uint8_t _type)
			: type_(_type)
		{}
	protected:
		std::uint8_t type() const {
			return this->type_;
		}
	private:
		std::uint8_t type_;
	};

	class encrypted_reply final : public typed_reply {
	public:
		encrypted_reply(const std::uint8_t type, bit_buffer* bbuffer)
			: typed_reply(type)
		{
			this->buffer_.append(bbuffer->get_buffer());
		}

		encrypted_reply(const std::uint8_t type, byte_buffer* bbuffer)
			: typed_reply(type)
		{
			this->buffer_.append(bbuffer->get_buffer());
		}

		std::string data() override;
	};

	class unencrypted_reply final : public typed_reply {
	public:
		unencrypted_reply(const std::uint8_t _type, bit_buffer* bbuffer)
			: typed_reply(_type)
		{
			this->buffer_.append(bbuffer->get_buffer());
		}

		unencrypted_reply(const std::uint8_t _type, byte_buffer* bbuffer)
			: typed_reply(_type)
		{
			this->buffer_.append(bbuffer->get_buffer());
		}

		std::string data() override;
	};

	class service_server;

	class remote_reply final {
	public:
		remote_reply(service_server* server, std::uint8_t _type)
			: type_(_type)
			, server_(server)
		{}

		void send(bit_buffer* buffer, bool encrypted);
		void send(byte_buffer* buffer, bool encrypted);

		std::uint8_t type() const {
			return this->type_;
		}
	private:
		std::uint8_t type_;
		service_server* server_;
	};

	class service_reply final {
	public:
		service_reply(service_server* _server, const std::uint8_t _type, const std::uint32_t _error, const bool _structed)
			: type_(_type)
			, error_(_error)
			, structed_(_structed)
			, reply_(_server, 1)
		{}

		std::uint64_t send() {
			static std::uint64_t id = 0x0000000000000000;
			const auto transaction_id = ++id;

			byte_buffer buffer;
			buffer.write_uint64(transaction_id);
			buffer.write_uint32(this->error_);
			buffer.write_ubyte(this->type_);

			if (!this->error_) {
				if (!this->structed_) {
					buffer.write_uint32(std::uint32_t(this->objects_.size()));
					if (!this->objects_.empty()) {
						buffer.write_uint32(std::uint32_t(this->objects_.size()));

						for (auto& object : this->objects_) {
							object->serialize(&buffer);
						}

						this->objects_.clear();
					}
				}
				else {
					if (!this->objects_.empty()) {
						this->objects_[0]->serialize(&buffer);
						this->objects_.clear();
					}
				}
			}
			else {
				buffer.write_uint64(transaction_id);
			}

			this->reply_.send(&buffer, true);
			return transaction_id;
		}

		void add(const std::shared_ptr<bdTaskResult>& object) {
			this->objects_.push_back(object);
		}

		void add(bdTaskResult* object) {
			this->add(std::shared_ptr<bdTaskResult>(object));
		}
	private:
		std::uint8_t type_;
		std::uint32_t error_;
		bool structed_;
		remote_reply reply_;
		std::vector<std::shared_ptr<bdTaskResult>> objects_;
	};

	class structure_reply final {
	public:
		structure_reply(service_server* _server, const std::uint8_t _type)
			: reply_(_server, _type, 0, 1)
		{}

		std::uint64_t send(const std::string& buffer) {
			auto result = new bdStructedDataBuffer;
			result->structed_data_protobuffer_ = buffer;

			this->reply_.add(result);

			return this->reply_.send();
		}
	private:
		service_reply reply_;
	};
}
