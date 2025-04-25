#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	class vec2_t {
	public:
		union {
			float v[2];		// 0x0000
			struct {
				float x;	// 0x0000
				float y;	// 0x0004
			};
		};

		vec2_t(float x, float y) {
			this->x = x;
			this->y = y;
		}
	};
	ENGINE_ASSERT_SZ(vec2_t, 0x0008);
}
