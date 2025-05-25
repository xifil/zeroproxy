#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	class GfxDrawSurfFields {
	public:
		std::uint64_t indirect_args_offset_ : 10;	// 0x0000
		std::uint64_t gp_batch_index_ : 16;			// 0x0000
		std::uint64_t object_id_ : 24;				// 0x0000
		std::uint64_t has_gfx_ent_index_ : 1;		// 0x0000
		std::uint64_t lightmap_index_ : 9;			// 0x0000
		std::uint64_t shadow_caster_ : 1;			// 0x0000
		std::uint64_t material_sorted_index_ : 16;	// 0x0008
		std::uint64_t tessellation_ : 3;			// 0x0008
		std::uint64_t pre_pass_ : 2;				// 0x0008
		std::uint64_t view_model_render_ : 1;		// 0x0008
		std::uint64_t low_res_shading_ : 1;			// 0x0008
		std::uint64_t surf_type_ : 4;				// 0x0008
		std::uint64_t primary_sort_key_ : 6;		// 0x0008
	};
	ENGINE_ASSERT_SZ(GfxDrawSurfFields, 0x0010);
}
