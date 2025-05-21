#pragma once
#include "engine/engine_common.hpp"

namespace t7s {
	class keyNumToNameMapping_t {
	public:
		int key_num_;					// 0x0000
	private:
		char pad_0004[0x0004];			// 0x0004
	public:
		const char* key_name_default_;	// 0x0008
		const char* key_name_xenon_;	// 0x0008
		const char* key_name_ps3_;		// 0x0008
	};
	ENGINE_ASSERT_SZ(keyNumToNameMapping_t, 0x0020);
}
