#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/GfxDecalVolumeMaterial.hpp"
#include "engine/iw8/GfxDrawSurf.hpp"
#include "engine/iw8/MaterialConstantBufferDef.hpp"
#include "engine/iw8/MaterialConstantDef.hpp"
#include "engine/iw8/MaterialTechniqueSet.hpp"
#include "engine/iw8/MaterialTextureDef.hpp"
#include "engine/iw8/enums/MaterialGeometryType.hpp"

namespace iw8 {
	class Material {
	public:
		const char* name_;									// 0x0000
		std::uint32_t contents_;							// 0x0008
		std::uint32_t surface_flags_;						// 0x000C
		float max_displacement_;							// 0x0010
		MaterialGeometryType material_type_;				// 0x0014
		std::uint8_t camera_region_;						// 0x0018
		std::uint8_t sort_key_;								// 0x0019
		union {
			std::uint16_t runtime_flags_;					// 0x001A
			std::uint16_t flags_;							// 0x001A
		};
		std::uint8_t texture_count_;						// 0x001C
		std::uint8_t constant_count_;						// 0x001D
		std::uint8_t constant_buffer_count_;				// 0x001E
		std::uint8_t layer_count;							// 0x001F
		std::uint16_t packed_atlas_data_size_;				// 0x0020
		std::uint8_t texture_atlas_row_count_;				// 0x0022
		std::uint8_t texture_atlas_column_count_;			// 0x0023
	private:
		char pad_0024[0x0004];								// 0x0024
	public:
		GfxDrawSurf draw_surf_;								// 0x0028
		std::uint8_t* packed_atlas_data_;					// 0x0038
		MaterialTechniqueSet* technique_set_;				// 0x0040
		MaterialTextureDef* texture_table_;					// 0x0048
		MaterialConstantDef* constant_table_;				// 0x0050
		GfxDecalVolumeMaterial* decal_volume_material_;		// 0x0058
		std::uint8_t* constant_buffer_index_;				// 0x0060
		MaterialConstantBufferDef* constant_buffer_table_;	// 0x0068
		const char** sub_materials_;						// 0x0070
	};
	ENGINE_ASSERT_SZ(Material, 0x0078);
}
