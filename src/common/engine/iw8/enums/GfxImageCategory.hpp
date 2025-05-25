#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	enum GfxImageCategory : std::int8_t {
		IMG_CATEGORY_UNKNOWN = 0,
		IMG_CATEGORY_AUTO_GENERATED = 1,
		IMG_CATEGORY_LIGHTMAP = 2,
		IMG_CATEGORY_LOAD_FROM_FILE = 3,
		IMG_CATEGORY_RAW = 4,
		IMG_CATEGORY_FIRST_UNMANAGED = 5,
		IMG_CATEGORY_RENDERTARGET = 5,
		IMG_CATEGORY_TEMP = 6
	};
}
