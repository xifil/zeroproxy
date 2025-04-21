#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/Collmap.hpp"
#include "engine/t6/DObjAnimMat.hpp"
#include "engine/t6/Material.hpp"
#include "engine/t6/PhysConstraints.hpp"
#include "engine/t6/PhysPreset.hpp"
#include "engine/t6/XBoneInfo.hpp"
#include "engine/t6/XModelCollSurf_s.hpp"
#include "engine/t6/XModelLodInfo.hpp"
#include "engine/t6/XSurface.hpp"

namespace t6 {
	class XModel {
	public:
		const char* name_;					// 0x0000
		std::uint8_t num_bones_;			// 0x0004
		std::uint8_t num_root_bones_;		// 0x0005
		std::uint8_t num_surfs_;			// 0x0006
		std::uint8_t lod_ramp_type_;		// 0x0007
		union _Bones {
			std::uint16_t* local_bone_names_;
			std::uint16_t* bone_names_;
		} bones_;							// 0x0008
		union _Parents {
			std::uint8_t* local_parent_list_;
			std::uint8_t* parent_list_;
		} parents_;							// 0x000C
		union _Quats {
			std::int16_t* local_quats_;
			std::int16_t* quats_;
		} quats_;							// 0x0010
		union _Trans {
			float* local_trans_;
			float* trans_;
		} trans_;							// 0x0014
		std::uint8_t* part_classification_;	// 0x0018
		DObjAnimMat* base_mat_;				// 0x001C
		XSurface* surfs_;					// 0x0020
		Material** material_handles_;		// 0x0024
		XModelLodInfo lod_info_[4];			// 0x0028
		XModelCollSurf_s* coll_surfs_;		// 0x0098
		int num_coll_surfs_;				// 0x009C
		int contents_;						// 0x00A0
		union _BoneInfos {
			XBoneInfo* local_bone_info_;
			XBoneInfo* bone_info_;
		} bone_infos_;						// 0x00A4
		float radius_;						// 0x00A8
		vec3_t mins_;						// 0x00AC
		vec3_t maxs_;						// 0x00B8
		std::int16_t num_lods_;				// 0x00C4
		std::int16_t coll_lod_;				// 0x00C6
		float* himip_inv_sq_radii_;			// 0x00C8
		int mem_usage_;						// 0x00CC
		int flags_;							// 0x00D0
		bool bad_;							// 0x00D4
	private:
		char pad_00D5[0x0003];				// 0x00D5
	public:
		PhysPreset* phys_preset_;			// 0x00D8
		std::uint8_t num_collmaps_;			// 0x00DC
	private:
		char pad_00DD[0x0003];				// 0x00DD
	public:
		Collmap* collmaps_;					// 0x00E0
		PhysConstraints* phys_constraints_;	// 0x00E4
		vec3_t lighting_origin_offset_;		// 0x00E8
		float lighting_origin_range_;		// 0x00F4
	};
	ENGINE_ASSERT_SZ(XModel, 0x00F8);
}
