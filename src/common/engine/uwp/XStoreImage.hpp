#pragma once
#include "engine/engine_common.hpp"

namespace uwp {
	class XStoreImage {
	public:
		const char* uri_;				// 0x0000
		std::uint32_t height_;			// 0x0008
		std::uint32_t width_;			// 0x000C
		const char* caption_;			// 0x0010
		const char* image_purpose_tag_;	// 0x0018
	};
	ENGINE_ASSERT_SZ(XStoreImage, 0x0020);
}
