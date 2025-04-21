#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class playlistGametype {
	public:
		const char* script_name;	// 0x0000
		const char* internal_name;	// 0x0004
		const char* localized_name;	// 0x0008
		const char* rules;			// 0x000C
	};
	ENGINE_ASSERT_SZ(playlistGametype, 0x0010);
}
