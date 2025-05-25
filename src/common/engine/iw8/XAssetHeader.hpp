#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/GfxDecalVolumeMaterial.hpp"
#include "engine/iw8/GfxImage.hpp"
#include "engine/iw8/LocalizeEntry.hpp"
#include "engine/iw8/Material.hpp"
#include "engine/iw8/MaterialSerializedShader.hpp"
#include "engine/iw8/MaterialTechniqueSet.hpp"
#include "engine/iw8/TTFDef.hpp"

namespace iw8 {
	union XAssetHeader {
		PhysicsLibrary* physics_library_;					// 0x0000
		PhysicsSFXEventAsset* physics_sfx_event_asset_;		// 0x0000
		PhysicsVFXEventAsset* physics_vfx_event_asset_;		// 0x0000
		PhysicsAsset* physics_asset_;						// 0x0000
		PhysicsFXPipeline* physics_fx_pipeline_;			// 0x0000
		PhysicsFXShape* physics_fx_shape_;					// 0x0000
		PhysicsDebugData* physics_debug_data_;				// 0x0000
		XAnimParts* parts_;									// 0x0000
		XModelSurfs* model_surfs_;							// 0x0000
		XModel* model_;										// 0x0000
		MayhemData* mayhem_;								// 0x0000
		Material* material_;								// 0x0000
		ComputeShader* compute_shader_;						// 0x0000
		MaterialSerializedShader* serialized_shader_;		// 0x0000
		MaterialTechniqueSet* technique_set_;				// 0x0000
		GfxImage* image_;									// 0x0000
		SndGlobals* sound_globals_;							// 0x0000
		SndBankResident* sound_bank_resident_;				// 0x0000
		SndBankTransient* sound_bank_transient_;			// 0x0000
		clipMap_t* clip_map_;								// 0x0000
		ComWorld* com_world_;								// 0x0000
		GlassWorld* glass_world_;							// 0x0000
		PathData* path_data_;								// 0x0000
		NavMeshData* nav_mesh_data_;						// 0x0000
		TacticalGraphData* tac_graph_data_;					// 0x0000
		MapEnts* map_ents_;									// 0x0000
		FxWorld* fx_world_;									// 0x0000
		GfxWorld* gfx_world_;								// 0x0000
		GfxWorldTransientZone* gfx_world_transient_zone_;	// 0x0000
		GfxIESProfile* ies_profile_;						// 0x0000
		GfxLightDef* light_def_;							// 0x0000
		GfxGradingClut* grading_clut_;						// 0x0000
		GfxFogSpline* fog_spline_;							// 0x0000
		AnimationClass* anim_class_;						// 0x0000
		PlayerAnimScript* player_anim_;						// 0x0000
		Gesture* gesture_;									// 0x0000
		LocalizeEntry* localize_;							// 0x0000
		WeaponAttachment* attachment_;						// 0x0000
		WeaponCompleteDef* weapon_;							// 0x0000
		ParticleSystemDef* vfx_;							// 0x0000
		FxImpactTable* impact_fx_;							// 0x0000
		SurfaceFxTable* surface_fx_;						// 0x0000
		RawFile* raw_file_;									// 0x0000
		ScriptFile* script_file_;							// 0x0000
		ScriptDebugData* script_debug_data_;				// 0x0000
		StringTable* string_table_;							// 0x0000
		LeaderboardDef* leaderboard_def_;					// 0x0000
		VirtualLeaderboardDef* virtual_leaderboard_def_;	// 0x0000
		DDLFile* ddl_file_;									// 0x0000
		TracerDef* tracer_def_;								// 0x0000
		VehicleDef* veh_def_;								// 0x0000
		AddonMapEnts* addon_map_ents_;						// 0x0000
		NetConstStrings* net_const_strings_;				// 0x0000
		LuaFile* lua_file_;									// 0x0000
		ScriptableDef* scriptable_;							// 0x0000
		EquipmentSoundTable* equip_snd_table_;				// 0x0000
		VectorField* vector_field_;							// 0x0000
		FxParticleSimAnimation* particle_sim_animation_;	// 0x0000
		StreamingInfo* streaming_info_;						// 0x0000
		LaserDef* laser_def_;								// 0x0000
		TTFDef* ttf_def_;									// 0x0000
		SuitDef* suit_def_;									// 0x0000
		SuitAnimPackage* suit_anim_package;					// 0x0000
		CameraDef* camera_def_;								// 0x0000
		HudOutlineDef* hud_outline_def_;					// 0x0000
		SpaceshipTargetDef* spaceship_target_def_;			// 0x0000
		RumbleInfo* rumble_;								// 0x0000
		RumbleGraph* rumble_graph_;							// 0x0000
		WeaponAnimPackage* weapon_anim_package_;			// 0x0000
		WeaponSFXPackage* weapon_sfx_package_;				// 0x0000
		WeaponVFXPackage* weapon_vfx_package_;				// 0x0000
		FootstepVFX* footstep_vfx_;							// 0x0000
		BehaviorTree* behavior_tree_;						// 0x0000
		Animset* animset_;									// 0x0000
		ASM* asm_asset_;									// 0x0000
		XAnimProceduralBones* procedural_bones_;			// 0x0000
		XAnimDynamicBones* dynamic_bones_;					// 0x0000
		ReticleDef* reticle_def_;							// 0x0000
		XAnimCurve* xanim_curve_;							// 0x0000
		CoverSelector* cover_selector_;						// 0x0000
		EnemySelector* enemy_selector_;						// 0x0000
		ClientCharacter* client_character_;					// 0x0000
		ClothAsset* cloth_asset_;							// 0x0000
		CinematicMotionDef* cinematic_motion_;				// 0x0000
		AccessoryDef* accessory_;							// 0x0000
		LocDmgTable* loc_dmg_table_;						// 0x0000
		BulletPenetration* bullet_penetration_;				// 0x0000
		ScriptBundle* script_bundle_;						// 0x0000
		BlendSpace2DDef* blend_space_2D_def_;				// 0x0000
		XCam* xcam_;										// 0x0000
		Camo* camo_;										// 0x0000
		XCompositeModelDef* composite_model_;				// 0x0000
		XModelDetailCollision* model_detail_collision_;		// 0x0000
		StreamKey* stream_key_;								// 0x0000
		StreamTreeOverride* stream_tree_override_;			// 0x0000
		KeyValuePairs* key_value_pairs_;					// 0x0000
		StTerrain* st_terrain_;								// 0x0000
		NativeScriptPatchFile* native_script_patch_;		// 0x0000
		CollisionTile* collision_tile_;						// 0x0000
		ExecutionDef* execution_def_;						// 0x0000
		CarryObjectDef* carry_object_def_;					// 0x0000
		SoundBankListDef* sound_bank_list_def_;				// 0x0000
		GfxDecalVolumeMaterial* decal_volume_material_;		// 0x0000
		GfxDecalVolumeMask* decal_volume_mask_;				// 0x0000
		DynEntityList* dyn_entity_list_;					// 0x0000
		void* data_;										// 0x0000
		FxWorldTransientZone* fx_world_transient_zone_;		// 0x0000
		DLogSchema* dlog_schema_;							// 0x0000
		MapEdgeList* map_edge_list_;						// 0x0000
	};
	ENGINE_ASSERT_SZ(XAssetHeader, 0x0008);
}
