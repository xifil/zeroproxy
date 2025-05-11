#pragma once
#include "common_core.hpp"

#define ENGINE_ASSERT_SZ(cls, sz) static_assert(sizeof(cls) == sz, #cls " is not " #sz " bytes in size.")

namespace iw4 {
	using Material = void;
}

namespace iw6 {
	using Material = void;
	using snd_alias_list_t = void;
}

namespace iw8 {
	using AccessoryDef = void;
	using AddonMapEnts = void;
	using AnimationClass = void;
	using Animset = void;
	using ASM = void;
	using BehaviorTree = void;
	using BlendSpace2DDef = void;
	using BulletPenetration = void;
	using CameraDef = void;
	using Camo = void;
	using CarryObjectDef = void;
	using CinematicMotionDef = void;
	using ClientCharacter = void;
	using clipMap_t = void;
	using ClothAsset = void;
	using CollisionTile = void;
	using ComputeShader = void;
	using ComWorld = void;
	using CoverSelector = void;
	using DDLFile = void;
	using DLogSchema = void;
	using DynEntityList = void;
	using EnemySelector = void;
	using EquipmentSoundTable = void;
	using ExecutionDef = void;
	using FootstepVFX = void;
	using FxImpactTable = void;
	using FxParticleSimAnimation = void;
	using FxWorld = void;
	using FxWorldTransientZone = void;
	using Gesture = void;
	using GfxDecalVolumeMaterial = void;
	using GfxDecalVolumeMask = void;
	using GfxFogSpline = void;
	using GfxGradingClut = void;
	using GfxIESProfile = void;
	using GfxImage = void;
	using GfxLightDef = void;
	using GfxWorld = void;
	using GfxWorldTransientZone = void;
	using GlassWorld = void;
	using HudOutlineDef = void;
	using KeyValuePairs = void;
	using LaserDef = void;
	using LeaderboardDef = void;
	using LocalizeEntry = void;
	using LocDmgTable = void;
	using LuaFile = void;
	using MapEdgeList = void;
	using MapEnts = void;
	using Material = void;
	using MaterialSerializedShader = void;
	using MaterialTechniqueSet = void;
	using MayhemData = void;
	using NativeScriptPatchFile = void;
	using NavMeshData = void;
	using NetConstStrings = void;
	using ParticleSystemDef = void;
	using PathData = void;
	using PlayerAnimScript = void;
	using PhysicsAsset = void;
	using PhysicsDebugData = void;
	using PhysicsFXPipeline = void;
	using PhysicsFXShape = void;
	using PhysicsLibrary = void;
	using PhysicsSFXEventAsset = void;
	using PhysicsVFXEventAsset = void;
	using RawFile = void;
	using ReticleDef = void;
	using RumbleGraph = void;
	using RumbleInfo = void;
	using ScriptableDef = void;
	using ScriptBundle = void;
	using ScriptDebugData = void;
	using ScriptFile = void;
	using SndBankResident = void;
	using SndBankTransient = void;
	using SndGlobals = void;
	using SoundBankListDef = void;
	using SpaceshipTargetDef = void;
	using StreamingInfo = void;
	using StreamKey = void;
	using StreamTreeOverride = void;
	using StringTable = void;
	using StTerrain = void;
	using SuitAnimPackage = void;
	using SuitDef = void;
	using SurfaceFxTable = void;
	using SvClientMP = void;
	using TacticalGraphData = void;
	using TracerDef = void;
	using TTFDef = void;
	using VectorField = void;
	using VehicleDef = void;
	using VirtualLeaderboardDef = void;
	using WeaponAnimPackage = void;
	using WeaponAttachment = void;
	using WeaponCompleteDef = void;
	using WeaponSFXPackage = void;
	using WeaponVFXPackage = void;
	using XAnimCurve = void;
	using XAnimDynamicBones = void;
	using XAnimParts = void;
	using XAnimProceduralBones = void;
	using XCam = void;
	using XCompositeModelDef = void;
	using XModel = void;
	using XModelDetailCollision = void;
	using XModelSurfs = void;
	using XZoneTemporaryLoadData = void;
}

namespace uwp {
	using XStoreContextHandle = class XStoreContext*;
	using XStoreLicenseHandle = class XStoreLicense*;
	using XStoreProductQueryHandle = class XStoreProductQuery*;
	using XTaskQueueHandle = class XTaskQueueObject*;
	using XUserHandle = class XUser*;

	using XStoreGameLicenseChangedCallback = void(void* context);
	using XStorePackageLicenseLostCallback = void(void* context);
}
