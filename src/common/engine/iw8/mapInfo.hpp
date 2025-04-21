#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	class mapInfo {
	public:
		char map_name_[32];					// 0x0000
		char map_load_name_[16];			// 0x0020
		char map_description_[32];			// 0x0030
		char map_load_image_[32];			// 0x0050
		char map_vote_image_[32];			// 0x0070
		char map_camo_types_[2][16];		// 0x0090
		char map_default_game_type_[32];	// 0x00B0
		char map_game_types_[1024];			// 0x00D0
		int is_aliens_map_;					// 0x04D0
		int map_pack_;						// 0x04D4
	};
	ENGINE_ASSERT_SZ(mapInfo, 0x04D8);
}