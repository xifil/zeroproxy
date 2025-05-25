#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	class streamer_handle_t {
	public:
		std::uint64_t data_;	// 0x0000
	};
	ENGINE_ASSERT_SZ(streamer_handle_t, 0x0008);
}
