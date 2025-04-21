#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/enums/AttachPointType.hpp"
#include "engine/t6/enums/ConstraintType.hpp"
#include "engine/t6/Material.hpp"
#include "engine/t6/vec3_t.hpp"

namespace t6 {
	class PhysConstraint {
	public:
		std::uint16_t target_name_;				// 0x0000
	private:
		char pad_0002[0x0002];					// 0x0002
	public:
		ConstraintType type_;					// 0x0004
		AttachPointType attach_point_type1_;	// 0x0008
		int target_index1_;						// 0x000C
		std::uint16_t target_ent1_;				// 0x0010
	private:
		char pad_0012[0x0002];					// 0x0012
	public:
		const char* target_bone1_;				// 0x0014
		AttachPointType attach_point_type2_;	// 0x0018
		int target_index2_;						// 0x001C
		std::uint16_t target_ent2_;				// 0x0020
	private:
		char pad_0022[0x0002];					// 0x0022
	public:
		const char* target_bone2_;				// 0x0024
		vec3_t offset_;							// 0x0028
		vec3_t pos_;							// 0x0034
		vec3_t pos2_;							// 0x0040
		vec3_t dir_;							// 0x004C
		int flags_;								// 0x0058
		int timeout_;							// 0x005C
		int min_health_;						// 0x0060
		int max_health_;						// 0x0064
		float distance_;						// 0x0068
		float damp_;							// 0x006C
		float power_;							// 0x0070
		vec3_t scale_;							// 0x0074
		float spin_scale_;						// 0x0080
		float min_angle_;						// 0x0084
		float max_angle_;						// 0x0088
		Material* material_;					// 0x008C
		int constraint_handle_;					// 0x0090
		int rope_index_;						// 0x0094
		int centity_num_[4];					// 0x0098
	};
	ENGINE_ASSERT_SZ(PhysConstraint, 0x00A8);
}
