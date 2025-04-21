#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/field_t.hpp"
#include "engine/t6/KeyState.hpp"
#include "engine/t6/enums/LocSelInputState.hpp"

namespace t6 {
	class PlayerKeyState {
	public:
		field_t chat_field_;					// 0x0000
		int chat_team_;							// 0x0118
		int overstrike_mode_;					// 0x011C
		int any_key_down_;						// 0x0120
		KeyState keys_[256];					// 0x0124
		LocSelInputState loc_sel_input_state_;	// 0x1524
	};
	ENGINE_ASSERT_SZ(PlayerKeyState, 0x1128);
}
