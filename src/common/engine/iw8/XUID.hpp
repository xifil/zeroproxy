#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/msg_t.hpp"

namespace iw8 {
	struct XUID {
		std::uint64_t id_;

		void deserialize(const msg_t* msg);
		void serialize(const msg_t* msg);
		XUID* from_hex_string(const char* xuid_string);
		XUID* from_msg(const msg_t* msg);
		XUID* from_string(const char* xuid_string);
		XUID* from_uint64(std::uint64_t id);
		XUID* from_universal_id(std::uint64_t id);

		std::uint64_t get_universal_id();

		bool is_null();
		bool is_valid();

		XUID* null_xuid();
		XUID* random_xuid();

		const char* to_dev_string();
		const char* to_hex_string();
		const char* to_string();

		bool operator !=(const XUID* xuid);
		XUID* operator =(const XUID* xuid);
		bool operator ==(const XUID* xuid);
	};
}
