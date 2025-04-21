#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/CardMemory.hpp"
#include "engine/t6/GfxStreamedPartInfo.hpp"
#include "engine/t6/GfxTexture.hpp"
#include "engine/t6/Picmip.hpp"

namespace t6 {
	class GfxImage {
	public:
		GfxTexture texture_;					// 0x0000
		std::uint8_t map_type_;					// 0x0004
		std::uint8_t semantic_;					// 0x0005
		std::uint8_t category_;					// 0x0006
		bool delay_load_pixels_;				// 0x0007
		Picmip picmip_;							// 0x0008
		bool no_picmip_;						// 0x000A
		std::uint8_t track_;					// 0x000B
		CardMemory card_memory_;				// 0x000C
		std::uint16_t width_;					// 0x0014
		std::uint16_t height_;					// 0x0016
		std::uint16_t depth_;					// 0x0018
		std::uint8_t level_count_;				// 0x001A
		std::uint8_t streaming_;				// 0x001B
		std::uint32_t base_size_;				// 0x001C
		std::uint8_t* pixels_;					// 0x0020
		GfxStreamedPartInfo streamed_parts_[1];	// 0x0024
		std::uint8_t streamed_part_count_;		// 0x003C
	private:
		char pad_003D[0x0003];					// 0x003D
	public:
		std::uint32_t loaded_size_;				// 0x0040
		std::uint8_t skipped_mip_levels_;		// 0x0044
	private:
		char pad_0045[0x0003];					// 0x0045
	public:
		const char* name_;						// 0x0048
		std::uint32_t hash_;					// 0x004C
	};
	ENGINE_ASSERT_SZ(GfxImage, 0x0050);
}
