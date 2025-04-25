#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/vec3_t.hpp"

namespace iw8 {
	class vec4_t {
	public:
		union {
			float v[4];		// 0x0000
			struct {
				float r;	// 0x0000
				float g;	// 0x0004
				float b;	// 0x0008
				float a;	// 0x000C
			};
			struct {
				float x;	// 0x0000
				float y;	// 0x0004
				float z;	// 0x0008
				float w;	// 0x000C
			};
			vec3_t xyz;		// 0x0000
		};

		vec4_t(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		vec4_t* get_ptr() {
			return this;
		}

		static inline vec4_t create_color(int r, int g, int b, int a) {
			return vec4_t(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
		}
	};
	ENGINE_ASSERT_SZ(vec4_t, 0x0010);
}
