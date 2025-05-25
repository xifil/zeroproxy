#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/GfxDrawSurfFields.hpp"
#include "engine/iw8/Packed128.hpp"

namespace iw8 {
	union GfxDrawSurf {
		GfxDrawSurfFields fields_;	// 0x0000
		Packed128 packed_;			// 0x0000
	};
	ENGINE_ASSERT_SZ(GfxDrawSurf, 0x0010);
}
