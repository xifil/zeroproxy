#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/GfxImage.hpp"

namespace iw8 {
	class MaterialTextureDef {
	public:
		std::uint8_t index_;	// 0x0000
	private:
		char pad_0001[0x0007];	// 0x0001
	public:
		GfxImage* image_;		// 0x0008
	};
	ENGINE_ASSERT_SZ(MaterialTextureDef, 0x0010);
}
