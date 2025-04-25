#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	class vec3_t {
	public:
		union {
			float v[3];		// 0x0000
			struct {
				float x;	// 0x0000
				float y;	// 0x0004
				float z;	// 0x0008
			};
		};

		vec3_t(float x, float y, float z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}
	};
	ENGINE_ASSERT_SZ(vec3_t, 0x000C);
}
