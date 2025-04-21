#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/GfxImageLoadDef.hpp"
#include <d3d11.h>

namespace t6 {
	union GfxTexture {
		ID3D11ShaderResourceView* base_map_;	// 0x0000
		GfxImageLoadDef* load_def_;				// 0x0000
	};
	ENGINE_ASSERT_SZ(GfxTexture, 0x0004);
}
