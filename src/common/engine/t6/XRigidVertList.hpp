#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/XSurfaceCollisionTree.hpp"

namespace t6 {
	class XRigidVertList {
	public:
		std::uint16_t bone_offset_;				// 0x0000
		std::uint16_t vert_count_;				// 0x0002
		std::uint16_t tri_offset_;				// 0x0004
		std::uint16_t tri_count_;				// 0x0006
		XSurfaceCollisionTree* collision_tree_;	// 0x0008
	};
	ENGINE_ASSERT_SZ(XRigidVertList, 0x000C);
}
