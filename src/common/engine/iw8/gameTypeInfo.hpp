#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	class gameTypeInfo {
	public:
		char game_type_internal_name_[12];		// 0x0000
		char game_type_name_[32];				// 0x000C
		char customized_game_type_name_[64];	// 0x002C
		char customized_game_type_desc_[64];	// 0x006C
	};
	ENGINE_ASSERT_SZ(gameTypeInfo, 0x00AC);
}