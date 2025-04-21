#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	enum class ConstraintType : int {
		CONSTRAINT_NONE = 0x0,
		CONSTRAINT_POINT = 0x1,
		CONSTRAINT_DISTANCE = 0x2,
		CONSTRAINT_HINGE = 0x3,
		CONSTRAINT_JOINT = 0x4,
		CONSTRAINT_ACTUATOR = 0x5,
		CONSTRAINT_FAKE_SHAKE = 0x6,
		CONSTRAINT_LAUNCH = 0x7,
		CONSTRAINT_ROPE = 0x8,
		CONSTRAINT_LIGHT = 0x9,
		NUM_CONSTRAINT_TYPES = 0xA
	};
}
