#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/XPakEntryInfo.hpp"
#include "engine/iw8/enums/GfxImageStreamLevelCountAndSize.hpp"

namespace iw8 {
	class GfxImageStreamData {
	public:
		XPakEntryInfo xpak_entry_;								// 0x0000
		GfxImageStreamLevelCountAndSize level_count_and_size_;	// 0x0020
		std::uint16_t width_;									// 0x0024
		std::uint16_t height_;									// 0x0026
	};
	ENGINE_ASSERT_SZ(GfxImageStreamData, 0x0028);
}
