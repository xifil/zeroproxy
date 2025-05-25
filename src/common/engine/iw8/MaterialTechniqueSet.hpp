#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/MaterialTechnique.hpp"
#include "engine/iw8/TechniqueMask.hpp"
#include "engine/iw8/enums/MaterialGeometryType.hpp"

namespace iw8 {
	class MaterialTechniqueSet {
	public:
		const char* name_;						// 0x0000
		std::uint64_t flags_;					// 0x0008
		MaterialGeometryType material_type_;	// 0x0010
	private:
		char pad_0014[0x0004];					// 0x0014
	public:
		TechniqueMask technique_mask_;			// 0x0018
		MaterialTechnique** masked_techniques_;	// 0x0038
	};
	ENGINE_ASSERT_SZ(MaterialTechniqueSet, 0x0040);
}
