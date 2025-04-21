#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/vec4_t.hpp"

namespace t6 {
	class GfxWaterBuffer {
	public:
		std::uint32_t m_BufferSize;	// 0x0000
		vec4_t* m_Buffer;			// 0x0004
	};
	ENGINE_ASSERT_SZ(GfxWaterBuffer, 0x0008);
}
