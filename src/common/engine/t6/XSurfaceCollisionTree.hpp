#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/vec3_t.hpp"
#include "engine/t6/XSurfaceCollisionLeaf.hpp"
#include "engine/t6/XSurfaceCollisionNode.hpp"

namespace t6 {
	class XSurfaceCollisionTree {
	public:
		vec3_t trans_;					// 0x0000
		vec3_t scale_;					// 0x000C
		std::uint32_t node_count_;		// 0x0018
		XSurfaceCollisionNode* nodes_;	// 0x001C
		std::uint32_t leaf_count_;		// 0x0020
		XSurfaceCollisionLeaf* leafs_;	// 0x0024
	};
	ENGINE_ASSERT_SZ(XSurfaceCollisionTree, 0x0028);
}
