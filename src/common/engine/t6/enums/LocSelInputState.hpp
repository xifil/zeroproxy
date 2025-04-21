#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	enum class LocSelInputState {
		LOC_SEL_INPUT_NONE = 0x0,
		LOC_SEL_INPUT_CONFIRM = 0x1,
		LOC_SEL_INPUT_YAW = 0x2,
		LOC_SEL_INPUT_CANCEL = 0x3
	};
}
