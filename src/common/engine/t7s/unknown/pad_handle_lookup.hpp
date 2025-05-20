#pragma once
#include "engine/engine_common.hpp"

namespace t7s {
	class pad_handle_lookup {
	public:
		int handle_id_;	// 0x0000
		int status_;	// 0x0004
	};
	ENGINE_ASSERT_SZ(pad_handle_lookup, 0x0008);
}
