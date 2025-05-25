#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/GfxImage.hpp"
#include "engine/iw8/vec3_t.hpp"

namespace iw8 {
	class GfxDecalVolumeMaterial {
	public:
		const char* name_;									// 0x0000
		GfxImage* channels_[6];								// 0x0008
		std::uint32_t flags_;								// 0x0038
		vec3_t color_tint_;									// 0x003C
		float alpha_dissolve_params_;						// 0x0048
		float emissive_scale_;								// 0x004C
		std::uint32_t packed_displacement_scale_and_bias_;	// 0x0050
		float displacement_cutoff_distance_;				// 0x0054
		float displacement_cutoff_falloff_;					// 0x0058
		std::uint32_t packed_temperature_base_and_scale_;	// 0x005C
		std::uint8_t texture_atlas_row_count_;				// 0x0060
		std::uint8_t texture_atlas_column_count_;			// 0x0061
		std::uint8_t padding_[6];							// 0x0062
	};
	ENGINE_ASSERT_SZ(GfxDecalVolumeMaterial, 0x0068);
}
