#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/streamer_handle_t.hpp"

namespace iw8 {
	union GfxImagePixels {
		streamer_handle_t streamed_data_handle_;	// 0x0000
		std::uint8_t* resident_data_;				// 0x0000
	};
	ENGINE_ASSERT_SZ(GfxImagePixels, 0x0008);
}
