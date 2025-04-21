#pragma once
#include "engine/engine_common.hpp"

namespace t9 {
	enum class LobbyNetworkMode : std::uint32_t {
		LOBBY_NETWORKMODE_INVALID = 0xFFFFFFFF,
		LOBBY_NETWORKMODE_UNKNOWN = 0,
		LOBBY_NETWORKMODE_LAN = 1,
		LOBBY_NETWORKMODE_LOCAL = 1,
		LOBBY_NETWORKMODE_LIVE = 2,
		LOBBY_NETWORKMODE_COUNT = 3
	};
}