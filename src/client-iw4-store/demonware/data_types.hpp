#pragma once
#include "common.hpp"
#include "demonware/byte_buffer.hpp"

namespace demonware {
	class bdTaskResult {
	public:
		virtual ~bdTaskResult() = default;

		virtual void serialize(byte_buffer*) {}
		virtual void deserialize(byte_buffer*) {}
	};

	class bdStringResult final : public bdTaskResult {
	public:
		std::string content_ = "";

		void serialize(byte_buffer* buffer) override {
			buffer->write_string(this->content_);
		}

		void deserialize(byte_buffer* buffer) override {
			buffer->read_string(&this->content_);
		}
	};

	class bdUInt64Result final : public bdTaskResult {
	public:
		std::uint64_t value_ = 0;

		void serialize(byte_buffer* buffer) override {
			buffer->write_uint64(this->value_);
		}

		void deserialize(byte_buffer* buffer) override {
			buffer->read_uint64(&this->value_);
		}
	};

	class bdBoolResult final : public bdTaskResult {
	public:
		bool value_ = false;

		void serialize(byte_buffer* buffer) override {
			buffer->write_bool(this->value_);
		}

		void deserialize(byte_buffer* buffer) override {
			buffer->read_bool(&this->value_);
		}
	};

	class bdTimeStamp final : public bdTaskResult {
	public:
		std::uint32_t unix_time_ = 0;

		void serialize(byte_buffer* buffer) override {
			buffer->write_uint32(this->unix_time_);
		}

		void deserialize(byte_buffer* buffer) override {
			buffer->read_uint32(&this->unix_time_);
		}
	};

	class bdDMLInfo : public bdTaskResult {
	public:
		std::string country_code_ = "";	// Char [3]
		std::string country_ = "";		// Char [65]
		std::string region_ = "";		// Char [65]
		std::string city_ = "";			// Char [129]
		float latitude_ = 0.f;
		float longitude_ = 0.f;
		std::uint32_t asn_ = 0;			// Autonomous System Number.
		std::string timezone_ = "";

		void serialize(byte_buffer* buffer) override {
			buffer->write_string(this->country_code_);
			buffer->write_string(this->country_);
			buffer->write_string(this->region_);
			buffer->write_string(this->city_);
			buffer->write_float(this->latitude_);
			buffer->write_float(this->longitude_);
			buffer->write_uint32(this->asn_);
			buffer->write_string(this->timezone_);
		}

		void deserialize(byte_buffer* buffer) override {
			buffer->read_string(&this->country_code_);
			buffer->read_string(&this->country_);
			buffer->read_string(&this->region_);
			buffer->read_string(&this->city_);
			buffer->read_float(&this->latitude_);
			buffer->read_float(&this->longitude_);
			buffer->read_uint32(&this->asn_);
			buffer->read_string(&this->timezone_);
		}
	};

	class bdDMLHierarchicalInfo final : public bdDMLInfo {
	public:
		std::uint32_t tier0_ = 0;
		std::uint32_t tier1_ = 0;
		std::uint32_t tier2_ = 0;
		std::uint32_t tier3_ = 0;
		std::uint32_t confidence_ = 0;

		void serialize(byte_buffer* buffer) override {
			bdDMLInfo::serialize(buffer);

			buffer->write_uint32(this->tier0_);
			buffer->write_uint32(this->tier1_);
			buffer->write_uint32(this->tier2_);
			buffer->write_uint32(this->tier3_);
			buffer->write_uint32(this->confidence_);
		}

		void deserialize(byte_buffer* buffer) override {
			bdDMLInfo::deserialize(buffer);

			buffer->read_uint32(&this->tier0_);
			buffer->read_uint32(&this->tier1_);
			buffer->read_uint32(&this->tier2_);
			buffer->read_uint32(&this->tier3_);
			buffer->read_uint32(&this->confidence_);
		}
	};

	class bdPublicProfileInfo final : public bdTaskResult {
	public:
		std::uint64_t entity_id_ = 0;
		int version_ = 0;
		std::string ddl_ = "";

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

	class bdFileMetaData final : public bdTaskResult {
	public:
		std::uint64_t file_id_ = 0;
		std::uint32_t create_time_ = 0;
		std::uint32_t modified_time_ = 0;
		std::uint32_t file_size_ = 0;
		std::uint64_t owner_id_ = 0;
		std::string owner_name_ = "";
		std::uint16_t file_slot_ = 0;
		std::string file_name_ = "";
		std::string url_ = "";
		std::uint16_t category_ = 0;
		std::string metadata_ = "";
		std::uint32_t summary_file_size_ = 0;
		std::map<std::uint64_t, std::uint64_t> tags_;
		std::uint32_t num_copies_made_ = 0;
		std::uint64_t origin_id_ = 0;

		void serialize(byte_buffer* buffer) override {
			buffer->write_uint64(this->file_id_);
			buffer->write_uint32(this->create_time_);
			buffer->write_uint32(this->modified_time_);
			buffer->write_uint32(this->file_size_);
			buffer->write_uint64(this->owner_id_);
			buffer->write_string(this->owner_name_);
			buffer->write_uint16(this->file_slot_);
			buffer->write_string(this->file_name_);
			buffer->write_string(this->url_);
			buffer->write_uint16(this->category_);
			buffer->write_blob(this->metadata_);
			buffer->write_uint32(this->summary_file_size_);
			buffer->write_array(10, tags_);
			buffer->write_uint32(this->num_copies_made_);
			buffer->write_uint64(this->origin_id_);
		}
	};

	class bdURL final : public bdTaskResult {
	public:
		std::string url_ = "";
		std::uint16_t server_type_ = 0;
		std::string server_index_ = "";
		std::uint64_t file_id_ = 0;

		void serialize(byte_buffer* buffer) override {
			buffer->write_string(this->url_);
			buffer->write_uint16(this->server_type_);
			buffer->write_string(this->server_index_);
			buffer->write_uint64(this->file_id_);
		}

		void deserialize(byte_buffer* buffer) override {
			buffer->read_string(&this->url_);
			buffer->read_uint16(&this->server_type_);
			buffer->read_string(&this->server_index_);
			buffer->read_uint64(&this->file_id_);
		}
	};

	class bdStructedDataBuffer final : public bdTaskResult {
	public:
		std::string structed_data_protobuffer_ = "";

		void serialize(byte_buffer* buffer) override {
			buffer->write_struct(this->structed_data_protobuffer_);
		}

		void deserialize(byte_buffer* buffer) override {
			buffer->read_struct(&this->structed_data_protobuffer_);
		}
	};
}
