#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	enum class DWOnlineStatus : std::int32_t {
		DW_LIVE_DISCONNECTED = 0x0,
		DW_LIVE_CONNECTING = 0x1,
		DW_LIVE_CONNECTED = 0x2
	};
}
