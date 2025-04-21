#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/vec3_t.hpp"
#include "engine/t6/vec4_t.hpp"

namespace t6 {
	class DObjAnimMat {
	public:
		vec4_t quat_;			// 0x0000
		vec3_t trans_;			// 0x0010
		float trans_weight_;	// 0x001C
	};
	ENGINE_ASSERT_SZ(DObjAnimMat, 0x0020);
}
