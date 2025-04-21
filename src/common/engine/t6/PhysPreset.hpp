#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/vec3_t.hpp"

namespace t6 {
	class PhysPreset {
	public:
		const char* name_;				// 0x0000
		int flags_;						// 0x0004
		float mass_;					// 0x0008
		float bounce_;					// 0x000C
		float friction_;				// 0x0010
		float bullet_force_scale_;		// 0x0014
		float explosive_force_scale_;	// 0x0018
		const char* snd_alias_prefix_;	// 0x001C
		float pieces_spread_fraction_;	// 0x0020
		float pieces_upward_velocity_;	// 0x0024
		int can_float_;					// 0x0028
		float gravity_scale_;			// 0x002C
		vec3_t center_of_mass_offset_;	// 0x0030
		vec3_t buoyancy_box_min_;		// 0x003C
		vec3_t buoyancy_box_max_;		// 0x0048
	};
	ENGINE_ASSERT_SZ(PhysPreset, 0x0054);
}
