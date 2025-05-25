#pragma once
#include "common.hpp"

#include <engine/iw8/DB_AuthSignature.hpp>
#include <engine/iw8/dvar_t.hpp>
#include <engine/iw8/gameTypeInfo.hpp>
#include <engine/iw8/LocalUserPresenceData.hpp>
#include <engine/iw8/lua_State.hpp>
#include <engine/iw8/luaL_Reg.hpp>
#include <engine/iw8/mapInfo.hpp>
#include <engine/iw8/XAssetList.hpp>
#include <engine/iw8/XUID.hpp>
#include <engine/iw8/XZoneMemory.hpp>
#include <engine/iw8/enums/DB_FastFileFailureMode.hpp>
#include <engine/iw8/enums/DWOnlineStatus.hpp>
#include <engine/iw8/unknown/bnet_class.hpp>

namespace functions {
	using CL_GetLocalClientSignInStateT = int(int controller_index);
	using Com_GameInfo_GetGameTypeForInternalNameT = iw8::gameTypeInfo*(const char* game_type_name);
	using Com_GameInfo_GetMapInfoForLoadNameT = iw8::mapInfo*(const char* map_name);
	using DB_FindXAssetHeaderT = iw8::XAssetHeader(iw8::XAssetType type, const char* given_name, int allow_create_default);
	using DB_LoadXFileT = int(const char* zone_name, iw8::XZoneMemory* zone_mem, iw8::XAssetList* asset_list, std::uint32_t zone_flags, bool was_paused,
		iw8::DB_FastFileFailureMode failure_mode, iw8::DB_AuthSignature* out_signature);
	using Dvar_FindVarByNameT = iw8::dvar_t*(const char* dvar_name);
	using Dvar_GetIntSafeT = int(const char* dvar_name);
	using Dvar_GetStringSafeT = const char*(const char* dvar_name);
	using Dvar_RegisterBoolT = iw8::dvar_t*(const char* dvar_name, bool value, std::uint32_t flags, const char* description);
	using dwGetLogOnStatusT = iw8::DWOnlineStatus(int controller_index);
	using GamerProfile_SetDataByNameT = void(int controller_index, const char* setting_name, float setting_value);
	using Info_ValueForKeyT = const char*(const char* s, const char* key);
	using Live_IsUserSignedInToDemonwareT = bool(int controller_index);
	using lua_pushbooleanT = void(iw8::lua_State* s, int b);
	using luaL_openlibT = void(iw8::lua_State* s, const char* lib_name, const iw8::luaL_Reg* l, std::uint32_t n_up);
	using R_EndFrameT = void();
	using SEH_StringEd_GetStringT = const char*(const char* psz_reference);
	using SV_Cmd_ArgvT = const char*(int arg_index);
	using SV_UpdateUserinfo_fT = void(iw8::SvClientMP* cl);
	using unk_IsUnsupportedGPUT = bool();
	using unk_IsUserSignedInToBNetT = bool();
}
