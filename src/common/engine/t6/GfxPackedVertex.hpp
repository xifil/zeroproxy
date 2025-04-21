#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/GfxColor.hpp"
#include "engine/t6/PackedTexCoords.hpp"
#include "engine/t6/PackedUnitVec.hpp"
#include "engine/t6/vec3_t.hpp"

namespace t6 {
	class GfxPackedVertex {
	public:
		vec3_t xyz_;				// 0x0000
		float binormal_sign_;		// 0x000C
		GfxColor color_;			// 0x0010
		PackedTexCoords tex_coord_;	// 0x0014
		PackedUnitVec normal_;		// 0x0018
		PackedUnitVec tangent_;		// 0x001C
	};
}
