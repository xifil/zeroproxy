#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	enum class connstate_t : int {
		CA_DISCONNECTED = 0x0,
		CA_CINEMATIC    = 0x1,
		CA_UICINEMATIC  = 0x2,
		CA_LOGO         = 0x3,
		CA_CONNECTING   = 0x4,
		CA_CHALLENGING  = 0x5,
		CA_CONNECTED    = 0x6,
		CA_SENDINGSTATS = 0x7,
		CA_LOADING      = 0x8,
		CA_PRIMED       = 0x9,
		CA_ACTIVE       = 0xA
	};
}
