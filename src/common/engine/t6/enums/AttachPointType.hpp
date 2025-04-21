#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	enum class AttachPointType : int {
		ATTACH_POINT_WORLD = 0x0,
		ATTACH_POINT_DYNENT = 0x1,
		ATTACH_POINT_ENT = 0x2,
		ATTACH_POINT_BONE = 0x3
	};
}
