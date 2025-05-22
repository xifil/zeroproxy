#pragma once
#include "common.hpp"
#include "demonware/byte_buffer.hpp"

#include <engine/t7s/enums/bdNATType.hpp>

namespace demonware {
	class bdTaskResult {
	public:
		virtual ~bdTaskResult() = default;

		virtual void serialize(byte_buffer* buffer) {}
		virtual void deserialize(byte_buffer* buffer) {}
	};

	class bdFileData final : public bdTaskResult {
	public:
		std::string file_data_;

		explicit bdFileData(std::string buffer)
			: file_data_(std::move(buffer))
		{}

		void serialize(byte_buffer* buffer) override {
			buffer->write_blob(this->file_data_);
		}

		void deserialize(byte_buffer* buffer) override {
			buffer->read_blob(&this->file_data_);
		}
	};

	class bdFileInfo final : public bdTaskResult {
	public:
		std::uint64_t file_id_;
		std::uint32_t create_time_;
		std::uint32_t modified_time_;
		bool priv_;
		std::uint64_t owner_id_;
		std::string file_name_;
		std::uint32_t file_size_;

		void serialize(byte_buffer* buffer) override {
			buffer->write_uint32(this->file_size_);
			buffer->write_uint64(this->file_id_);
			buffer->write_uint32(this->create_time_);
			buffer->write_uint32(this->modified_time_);
			buffer->write_bool(this->priv_);
			buffer->write_uint64(this->owner_id_);
			buffer->write_string(this->file_name_);
		}

		void deserialize(byte_buffer* buffer) override {
			buffer->read_uint32(&this->file_size_);
			buffer->read_uint64(&this->file_id_);
			buffer->read_uint32(&this->create_time_);
			buffer->read_uint32(&this->modified_time_);
			buffer->read_bool(&this->priv_);
			buffer->read_uint64(&this->owner_id_);
			buffer->read_string(&this->file_name_);
		}
	};

	class bdFileQueryResult final : public bdTaskResult {
	public:
		std::uint64_t user_id_;
		std::string platform_;
		std::string file_name_;
		std::uint32_t error_code_;
		std::string file_data_;

		void serialize(byte_buffer* data) override {
			data->write_uint64(this->user_id_);
			data->write_string(this->platform_);
			data->write_string(this->file_name_);
			data->write_uint32(this->error_code_);
			data->write_blob(this->file_data_);
		}

		void deserialize(byte_buffer* data) override {
			data->read_uint64(&this->user_id_);
			data->read_string(&this->platform_);
			data->read_string(&this->file_name_);
			data->read_uint32(&this->error_code_);
			data->read_blob(&this->file_data_);
		}
	};

	class bdTimeStamp final : public bdTaskResult {
	public:
		std::uint32_t unix_time_;

		void serialize(byte_buffer* buffer) override {
			buffer->write_uint32(this->unix_time_);
		}

		void deserialize(byte_buffer* buffer) override {
			buffer->read_uint32(&this->unix_time_);
		}
	};

	class bdDMLInfo : public bdTaskResult {
	public:
		std::string country_code_;	// Char [3]
		std::string country_;		// Char [65]
		std::string region_;		// Char [65]
		std::string city_;			// Char [129]
		float latitude_;
		float longitude_;

		void serialize(byte_buffer* buffer) override {
			buffer->write_string(this->country_code_);
			buffer->write_string(this->country_);
			buffer->write_string(this->region_);
			buffer->write_string(this->city_);
			buffer->write_float(this->latitude_);
			buffer->write_float(this->longitude_);
		}

		void deserialize(byte_buffer* buffer) override {
			buffer->read_string(&this->country_code_);
			buffer->read_string(&this->country_);
			buffer->read_string(&this->region_);
			buffer->read_string(&this->city_);
			buffer->read_float(&this->latitude_);
			buffer->read_float(&this->longitude_);
		}
	};

	class bdDMLRawData final : public bdDMLInfo {
	public:
		std::uint32_t asn_;	// Autonomous System Number.
		std::string timezone_;

		void serialize(byte_buffer* buffer) override {
			bdDMLInfo::serialize(buffer);

			buffer->write_uint32(this->asn_);
			buffer->write_string(this->timezone_);
		}

		void deserialize(byte_buffer* buffer) override {
			bdDMLInfo::deserialize(buffer);

			buffer->read_uint32(&this->asn_);
			buffer->read_string(&this->timezone_);
		}
	};

	class bdFile final : public bdTaskResult {
	public:
		std::uint64_t owner_id_;
		std::string platform_;
		std::string file_name_;
		std::uint32_t unk_;
		std::string data_;

		void serialize(byte_buffer* buffer) override {
			buffer->write_uint64(this->owner_id_);
			buffer->write_string(this->platform_);
			buffer->write_string(this->file_name_);
			buffer->write_uint32(this->unk_);
			buffer->write_blob(this->data_);
		}

		void deserialize(byte_buffer* buffer) override {
			buffer->read_uint64(&this->owner_id_);
			buffer->read_string(&this->platform_);
			buffer->read_string(&this->file_name_);
			buffer->read_uint32(&this->unk_);
			buffer->read_blob(&this->data_);
		}
	};

	class bdFile2 final : public bdTaskResult {
	public:
		std::uint32_t unk1_;
		std::uint32_t unk2_;
		std::uint32_t unk3_;
		bool priv_;
		std::uint64_t owner_id_;
		std::string platform_;
		std::string file_name_;
		std::string data_;

		void serialize(byte_buffer* buffer) override {
			buffer->write_uint32(this->unk1_);
			buffer->write_uint32(this->unk2_);
			buffer->write_uint32(this->unk3_);
			buffer->write_bool(this->priv_);
			buffer->write_uint64(this->owner_id_);
			buffer->write_string(this->platform_);
			buffer->write_string(this->file_name_);
			buffer->write_blob(this->data_);
		}

		void deserialize(byte_buffer* buffer) override {
			buffer->read_uint32(&this->unk1_);
			buffer->read_uint32(&this->unk2_);
			buffer->read_uint32(&this->unk3_);
			buffer->read_bool(&this->priv_);
			buffer->read_uint64(&this->owner_id_);
			buffer->read_string(&this->platform_);
			buffer->read_string(&this->file_name_);
			buffer->read_blob(&this->data_);
		}
	};

	class bdContextUserStorageFileInfo final : public bdTaskResult {
	public:
		std::uint32_t create_time_;
		std::uint32_t modifed_time_;
		bool priv_;
		std::uint64_t owner_id_;
		std::string account_type_;
		std::string file_name_;

		void serialize(byte_buffer* buffer) override {
			buffer->write_uint32(this->create_time_);
			buffer->write_uint32(this->modifed_time_);
			buffer->write_bool(this->priv_);
			buffer->write_uint64(this->owner_id_);
			buffer->write_string(this->account_type_);
			buffer->write_string(this->file_name_);
		}

		void deserialize(byte_buffer* buffer) override {
			buffer->read_uint32(&this->create_time_);
			buffer->read_uint32(&this->modifed_time_);
			buffer->read_bool(&this->priv_);
			buffer->read_uint64(&this->owner_id_);
			buffer->read_string(&this->account_type_);
			buffer->read_string(&this->file_name_);
		}
	};

	class bdPerformanceValue final : public bdTaskResult {
	public:
		std::uint64_t user_id_;
		std::int64_t performance_;

		void serialize(byte_buffer* buffer) override {
			buffer->write_uint64(this->user_id_);
			buffer->write_int64(this->performance_);
		}

		void deserialize(byte_buffer* buffer) override {
			buffer->read_uint64(&this->user_id_);
			buffer->read_int64(&this->performance_);
		}
	};

	class bdDDLChecksumResult final : public bdTaskResult {
	public:
		std::string checksum_{};
		bool checksum_matched_{};

		void serialize(byte_buffer* buffer) override {
			buffer->write_string(this->checksum_);
			buffer->write_bool(this->checksum_matched_);
		}

		void deserialize(byte_buffer* buffer) override {
			buffer->read_string(&this->checksum_);
		}
	};

	struct bdSockAddr final {
		bdSockAddr()
			: in_un_()
			, family_(AF_INET)
		{}

		union {
			struct {
				char b1_;
				char b2_;
				char b3_;
				char b4_;
			} c_addr_;

			std::uint32_t i_addr_;

			struct {
				std::uint16_t w1_;
				std::uint16_t w2_;
				std::uint16_t w3_;
				std::uint16_t w4_;
				std::uint16_t w5_;
				std::uint16_t w6_;
				std::uint16_t w7_;
				std::uint16_t w8_;
			} c_addr6_;

			char i_addr6_[16];
			char sockaddr_storage_[128];
		} in_un_;

		std::uint16_t family_;
	};

	struct bdInetAddr final : bdTaskResult {
		bdSockAddr addr_;

		bool is_valid() const {
			return (this->addr_.family_ == AF_INET /*|| this->m_addr.m_family == AF_INET6*/);
		}

		void serialize(byte_buffer* buffer) override {
			const auto data_types = buffer->is_using_data_types();
			buffer->set_use_data_types(false);

			if (this->addr_.family_ == AF_INET) {
				buffer->write(4, &this->addr_.in_un_.c_addr_);
			}

			buffer->set_use_data_types(data_types);
		}

		void deserialize(byte_buffer* buffer) override {
			const auto data_types = buffer->is_using_data_types();
			buffer->set_use_data_types(false);

			if (this->addr_.family_ == AF_INET) {
				buffer->read(4, &this->addr_.in_un_.c_addr_);
			}

			buffer->set_use_data_types(data_types);
		}
	};

	struct bdAddr final : bdTaskResult {
		bdInetAddr address_;
		std::uint16_t port_{};

		void serialize(byte_buffer* buffer) override {
			const bool data_types = buffer->is_using_data_types();
			buffer->set_use_data_types(false);

			this->address_.serialize(buffer);
			buffer->write_uint16(this->port_);

			buffer->set_use_data_types(data_types);
		}

		void deserialize(byte_buffer* buffer) override {
			const auto data_types = buffer->is_using_data_types();
			buffer->set_use_data_types(false);

			this->address_.deserialize(buffer);
			buffer->read_uint16(&this->port_);

			buffer->set_use_data_types(data_types);
		}
	};

	struct bdCommonAddr : bdTaskResult {
		bdAddr local_addrs_[5];
		bdAddr public_addr_;
		t7s::bdNATType nat_type_;
		std::uint32_t hash_;
		bool is_loopback_;

		void serialize(byte_buffer* buffer) override {
			const auto data_types = buffer->is_using_data_types();
			buffer->set_use_data_types(false);

			auto valid = true;
			for (std::uint32_t i = 0; i < 5 && i < ARRAYSIZE(this->local_addrs_) && valid; ++i) {
				this->local_addrs_[i].serialize(buffer);
				valid = this->local_addrs_[i].address_.is_valid();
			}

			if (valid) {
				this->public_addr_.serialize(buffer);
				buffer->write_byte(ENUM_UNDER(this->nat_type_));
			}

			buffer->set_use_data_types(data_types);
		}

		void deserialize(byte_buffer* buffer) override {
			const auto data_types = buffer->is_using_data_types();
			buffer->set_use_data_types(false);

			auto valid = true;
			for (std::uint32_t i = 0; i < ARRAYSIZE(this->local_addrs_) && valid; ++i) {
				bdAddr addr;
				addr.deserialize(buffer);
				this->local_addrs_[i] = addr;
				valid = this->local_addrs_[i].address_.is_valid();
			}

			if (valid) {
				this->public_addr_.deserialize(buffer);
				buffer->read_ubyte(PTR_AS(std::uint8_t*, &this->nat_type_));
			}

			buffer->set_use_data_types(data_types);
		}
	};

	class bdSessionID final : public bdTaskResult {
	public:
		std::uint64_t session_id_;

		void serialize(byte_buffer* buffer) override {
			buffer->write_blob(LPSTR(&this->session_id_), sizeof this->session_id_);
		}

		void deserialize(byte_buffer* buffer) override {
			int size{};
			char* data{};
			buffer->read_blob(&data, &size);

			if (data && static_cast<std::uint32_t>(size) >= sizeof(this->session_id_)) {
				this->session_id_ = DEREF_PTR_AS(std::uint64_t, data);
			}
		}
	};

	class bdMatchMakingInfo final : bdTaskResult {
		bdSessionID session_id_;
		std::string host_addr_;
		std::uint32_t game_type_;
		std::uint32_t max_players_;
		std::uint32_t num_players_;

		void serialize(byte_buffer* buffer) override {
			buffer->write_blob(this->host_addr_);
			this->session_id_.serialize(buffer);
			buffer->write_uint32(this->game_type_);
			buffer->write_uint32(this->max_players_);
			buffer->write_uint32(this->num_players_);
		}

		void deserialize(byte_buffer* buffer) override {
			buffer->read_blob(&this->host_addr_);
			buffer->read_uint32(&this->game_type_);
			buffer->read_uint32(&this->max_players_);
		}
	};

	class bdPublicProfileInfo final : public bdTaskResult {
	public:
		std::uint64_t entity_id_;
		std::int32_t version_;
		std::string ddl_;

		void serialize(byte_buffer* buffer) override {
			buffer->write_uint64(this->entity_id_);
			buffer->write_int32(this->version_);
			buffer->write_blob(this->ddl_);
		}

		void deserialize(byte_buffer* buffer) override {
			buffer->read_uint64(&this->entity_id_);
			buffer->read_int32(&this->version_);
			buffer->read_blob(&this->ddl_);
		}
	};
}
