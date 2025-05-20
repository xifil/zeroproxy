#pragma once
#include "engine/engine_common.hpp"

namespace t7s {
	class GamePad {
	public:
		bool connected_;		// 0x0000
		int pad_index_;			// 0x0004
	private:
		char pad_0008[0x0068];	// 0x0008
	};
	ENGINE_ASSERT_SZ(GamePad, 0x0070);
}
