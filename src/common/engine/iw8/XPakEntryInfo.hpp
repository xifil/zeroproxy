#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	class XPakEntryInfo {
	public:
		std::uint64_t key_;						// 0x0000
		std::int64_t offset_;					// 0x0008
		std::uint64_t size_;					// 0x0010
		std::uint64_t xpak_index_ : 8;			// 0x0018
		std::uint64_t compressed_ : 1;			// 0x0018
		std::uint64_t valid_ : 1;				// 0x0018
		std::uint64_t adjacent_left_type_ : 3;	// 0x0018
		std::uint64_t adjacent_right_type_ : 3;	// 0x0018
		std::uint64_t adjacent_left_ : 19;		// 0x0018
		std::uint64_t adjacent_right_ : 19;		// 0x0018
		std::uint64_t padding_ : 10;			// 0x0018
	};
	ENGINE_ASSERT_SZ(XPakEntryInfo, 0x0020);
}
