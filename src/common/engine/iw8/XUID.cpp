#if defined(_WIN64)
#include "engine/engine_common.hpp"
#include "engine/iw8/XUID.hpp"

#include "memory/memory.hpp"
#include "utils/string.hpp"

namespace iw8 {
	namespace {
		using I_irandT = std::int64_t(int min, int max);
		using MSG_ReadInt64T = std::uint64_t(const msg_t* msg);
		using MSG_WriteInt64T = void(const msg_t* msg, const std::uint64_t value);
		using Sys_MicrosecondsT = std::uint64_t();

		std::uint64_t atoui64(const std::string& str, int base) {
			try {
				return std::stoull(str, nullptr, base);
			}
			catch (...) {
				return 0;
			}
		}
	}

	void XUID::deserialize(const msg_t* msg) {
		static auto MSG_ReadInt64 = memory::sig_scan<MSG_ReadInt64T*>({}, "40 56 57 41 56 48 83 EC ? 8B 51 ? 48 8B F9 8B 71 ? 8B 41 ? 03 C6 44 8D 72 ? C1 E0 ? 44 3B F0 7E ? C7 01 ?"
			" ? ? ? 33 C0").get();
		this->id_ = MSG_ReadInt64(msg);
	}

	void XUID::serialize(const msg_t* msg) {
		static auto MSG_WriteInt64 = memory::sig_scan<MSG_WriteInt64T*>({}, "4C 8B C9 8B 49 ? 45 8B 41 ? 8D 41 ? 41 C1 E0 ? 41 3B C0 7E ? 41 C7 01 ? ? ? ? C3 41 83 39 ? 75 ? F6 C1 ?"
			" 74 ? 4C 8B C2").get();
		MSG_WriteInt64(msg, this->id_);
	}

	XUID* XUID::from_hex_string(const char* xuid_string) {
		this->id_ = atoui64(xuid_string, 16);
		return this;
	}

	XUID* XUID::from_msg(const msg_t* msg) {
		this->deserialize(msg);
		return this;
	}

	XUID* XUID::from_string(const char* xuid_string) {
		this->id_ = atoui64(xuid_string, 10);
		return this;
	}

	XUID* XUID::from_uint64(std::uint64_t id) {
		this->id_ = id;
		return this;
	}

	XUID* XUID::from_universal_id(std::uint64_t id) {
		this->id_ = id;
		return this;
	}

	std::uint64_t XUID::get_universal_id() {
		return this->id_;
	}

	bool XUID::is_null() {
		return this->id_ == 0;
	}

	bool XUID::is_valid() {
		return this->id_ != 0;
	}

	XUID* XUID::null_xuid() {
		this->id_ = 0;
		return this;
	}

	XUID* XUID::random_xuid() {
		static auto I_irand = memory::sig_scan<I_irandT*>({}, "69 05 ? ? ? ? ? ? ? ? 2B D1 48 63 D2").get();
		static auto Sys_Microseconds = memory::sig_scan<Sys_MicrosecondsT*>({}, "83 3D ? ? ? ? ? 49 B8 ? ? ? ? ? ? ? ? F2 0F 10 15").get();
		static auto I_irand_res = memory::sig_scan(game, "69 05 ? ? ? ? ? ? ? ? 2B D1 48 63 D2");

		std::uint32_t* rand_seed = holdrand;
		std::uint32_t backup_rand_seed = *rand_seed;
		this->id_ = 0ull;
		*rand_seed = Sys_Microseconds() & 0xFFFFFFFF;
		this->id_ = I_irand(1, INT_MAX);
		*rand_seed = backup_rand_seed;
		return this;
	}

	const char* XUID::to_dev_string() {
		return utils::string::va("%zu", this->id_);
	}

	const char* XUID::to_hex_string() {
		return utils::string::va("%zx", this->id_);
	}

	const char* XUID::to_string() {
		return utils::string::va("%zu", this->id_);
	}

	bool XUID::operator !=(const XUID* xuid) {
		return this->id_ != xuid->id_;
	}

	XUID* XUID::operator =(const XUID* xuid) {
		this->id_ = xuid->id_;
		return this;
	}

	bool XUID::operator ==(const XUID* xuid) {
		return this->id_ == xuid->id_;
	}
}
#endif
