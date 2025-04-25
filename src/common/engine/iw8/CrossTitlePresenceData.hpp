#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/enums/bdPlatformType.hpp"

namespace iw8 {
	class CrossTitlePresenceData {
	public:
		std::uint64_t platform_id_;	// 0x0000
		std::uint32_t version_;		// 0x0008
		std::uint32_t title_id_;	// 0x000C
		bdPlatformType platform_;	// 0x0010
		bool online_;				// 0x0011
	private:
		char pad_0012[0x0006];		// 0x0012
	};
	ENGINE_ASSERT_SZ(CrossTitlePresenceData, 0x0018);
}
