#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/vec3_t.hpp"
#include "engine/t6/XModel.hpp"

namespace t6 {
	class XModelPiece {
	public:
		XModel* model_;	// 0x0000
		vec3_t offset_;	// 0x0004
	};
	ENGINE_ASSERT_SZ(XModelPiece, 0x0010);
}
