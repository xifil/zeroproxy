#pragma once
#include "engine/engine_common.hpp"
#include "engine/uwp/XStoreImage.hpp"

namespace uwp {
	class XStoreVideo {
	public:
		const char* uri_;				// 0x0000
		std::uint32_t height_;			// 0x0008
		std::uint32_t width_;			// 0x000C
		const char* caption_;			// 0x0010
		const char* video_purpose_tag_;	// 0x0018
		XStoreImage preview_image_;		// 0x0020
	};
	ENGINE_ASSERT_SZ(XStoreVideo, 0x0040);
}
