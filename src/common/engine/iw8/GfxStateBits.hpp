#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/enums/GfxBlendStateBits.hpp"
#include "engine/iw8/enums/GfxOtherStateBits.hpp"

namespace iw8 {
	class GfxStateBits {
	public:
		GfxOtherStateBits other_bits_;	// 0x0000
		GfxBlendStateBits blend_bits_;	// 0x0008
	};
	ENGINE_ASSERT_SZ(GfxStateBits, 0x0010);
}
