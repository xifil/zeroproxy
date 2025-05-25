#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/GfxImageAtlasInfo.hpp"
#include "engine/iw8/GfxImageFallback.hpp"
#include "engine/iw8/GfxImagePixels.hpp"
#include "engine/iw8/GfxImageSemanticSpecific.hpp"
#include "engine/iw8/GfxImageStreamData.hpp"
#include "engine/iw8/enums/GfxImageCategory.hpp"
#include "engine/iw8/enums/GfxImageFlags.hpp"
#include "engine/iw8/enums/GfxPixelFormat.hpp"
#include "engine/iw8/enums/GfxTextureId.hpp"
#include "engine/iw8/enums/TextureSemantic.hpp"

namespace iw8 {
	class GfxImage {
	public:
		const char* name_;								// 0x0000
		std::uint8_t* packed_atlas_data_;				// 0x0008
		GfxTextureId texture_id_;						// 0x0010
		GfxPixelFormat format_;							// 0x0014
		GfxImageFlags flags_;							// 0x0018
		std::uint32_t total_size_;						// 0x001C
		GfxImageSemanticSpecific semantic_specific_;	// 0x0020
		std::uint16_t width_;							// 0x0024
		std::uint16_t height_;							// 0x0026
		std::uint16_t depth_;							// 0x0028
		std::uint16_t num_elements_;					// 0x002A
		GfxImageAtlasInfo atlas_info_;					// 0x002C
		TextureSemantic semantic_;						// 0x002E
		GfxImageCategory category_;						// 0x002F
		std::uint8_t level_count_;						// 0x0030
		std::uint8_t streamed_part_count_;				// 0x0031
		std::uint8_t decal_atlas_index_;				// 0x0032
		char freq_domain_metric_bias_;					// 0x0033
	private:
		char pad_0034[0x0004];							// 0x0034
	public:
		GfxImageStreamData streams_[4];					// 0x0038
		GfxImageFallback* fallback_;					// 0x00D8
		GfxImagePixels pixels_;							// 0x00E0
	};
	ENGINE_ASSERT_SZ(GfxImage, 0x00E8);
}
