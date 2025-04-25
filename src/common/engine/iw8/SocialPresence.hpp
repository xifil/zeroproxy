#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/CrossTitlePresenceData.hpp"

namespace iw8 {
	class SocialPresence {
	public:
		CrossTitlePresenceData cross_title_presence_data_;	// 0x0000
		std::uint32_t session_flags_;						// 0x0018
		char clan_tag_[12];									// 0x001C
		char version_;										// 0x0028
		char context_;										// 0x0029
		char game_type_;									// 0x002A
		char map_index_;									// 0x002B
		char flags_;										// 0x002C
		char input_type_;									// 0x002D
	private:
		char pad_002E[0x0002];								// 0x002E
	};
	ENGINE_ASSERT_SZ(SocialPresence, 0x0030);
}
