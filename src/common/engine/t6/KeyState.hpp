#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/enums/Bind_t.hpp"

namespace t6 {
	class KeyState {
	public:
		int down_;				// 0x0000
		int repeats_;			// 0x0004
		Bind_t binding_[2];		// 0x0008
	};
	ENGINE_ASSERT_SZ(KeyState, 0x0010);
}
