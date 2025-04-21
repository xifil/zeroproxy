#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/PhysConstraint.hpp"

namespace t6 {
	class PhysConstraints {
	public:
		const char* name_;			// 0x0000
		unsigned int count_;		// 0x0004
		PhysConstraint data_[16];	// 0x0008
	};
	ENGINE_ASSERT_SZ(PhysConstraints, 0x0A88);
}
