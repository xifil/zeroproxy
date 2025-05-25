#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/GfxImageAtlasSize.hpp"

namespace iw8 {
	union GfxImageAtlasInfo {
		GfxImageAtlasSize atlas_size_;			// 0x0000
		std::uint16_t packed_atlas_data_size_;	// 0x0000
	};
	ENGINE_ASSERT_SZ(GfxImageAtlasInfo, 0x0002);
}
