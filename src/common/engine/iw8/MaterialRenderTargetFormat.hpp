#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	class MaterialRenderTargetFormat {
	public:
		std::uint8_t ds_format_;			// 0x0000
		std::uint8_t color_rt_formats_[4];	// 0x0001
	};
	ENGINE_ASSERT_SZ(MaterialRenderTargetFormat, 0x0005);
}
