﻿#pragma once
#include "common_core.hpp"

#define ENGINE_ASSERT_SZ(cls, sz) static_assert(sizeof(cls) == sz, #cls " is not " #sz " bytes in size.")

namespace iw4s {
	using Material = void;
}

namespace iw6s {
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
	using GfxDecalVolumeMask = void;
	using GfxFogSpline = void;
	using GfxGradingClut = void;
	using GfxIESProfile = void;
	using GfxLightDef = void;
	using GfxWorld = void;
	using GfxWorldTransientZone = void;
	using GlassWorld = void;
	using HudOutlineDef = void;
	using KeyValuePairs = void;
	using LaserDef = void;
	using LeaderboardDef = void;
	using LocDmgTable = void;
	using LuaFile = void;
	using LUIGlobalPackage = void;
	using MapEdgeList = void;
	using MapEnts = void;
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

namespace t6s {
	using Glyph = void;
	using KerningPairs = void;
	using Material = void;
	using SndAliasList = void;
}

namespace t7s {
	using Glyph = void;
	using KerningPairs = void;
	using Material = void;

	class lua_Debug;
	class lua_State;

	using lua_Alloc = void*(*)(void*, void*, std::size_t, std::size_t);
	using lua_CFunction = int(*)(void*);
	using lua_Hook = void(*)(lua_State*, lua_Debug*);

	namespace hks {
		using DebugMapT = int(*)(const char* file_name, int lua_line);
		using EmergencyGCFailFuncT = void(*)(lua_State*, std::size_t);
		using LogFuncT = void(*)(lua_State*, const char*, ...);

		class Closure;
		class CClosure;
		class HashTable;
		class InternString;
		class Metatable;
		class Method;
		class StructInst;
		class UpValue;
		class UserData;
	}
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
