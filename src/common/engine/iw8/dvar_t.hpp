#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/BbConstUsageFlags.hpp"
#include "engine/iw8/DvarLimits.hpp"
#include "engine/iw8/DvarValue.hpp"

namespace iw8 {
	class dvar_t {
	public:
		const char* name_;							// 0x0000
		std::uint32_t checksum_;					// 0x0008
	private:
		char pad_000C[0x0004];						// 0x000C
	public:
		const char* description_;					// 0x0010
		std::uint32_t flags_;						// 0x0018
		std::uint8_t level_[1];						// 0x001C
		std::uint8_t type_;							// 0x001D
		bool modified_;								// 0x001E
	private:
		char pad_001F[0x0001];						// 0x001F
	public:
		std::uint16_t hash_next_;					// 0x0020
	private:
		char pad_0022[0x0006];						// 0x0022
	public:
		DvarValue current_;							// 0x0028
		DvarValue latched_;							// 0x0038
		DvarValue reset_;							// 0x0048
		DvarLimits domain_;							// 0x0058
		BbConstUsageFlags bb_const_usage_flags_;	// 0x0068
	};
	ENGINE_ASSERT_SZ(dvar_t, 0x0080);
}
