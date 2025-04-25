#pragma once
#include "common.hpp"

#include <engine/iw8/dvar_t.hpp>
#include <engine/iw8/gameTypeInfo.hpp>
#include <engine/iw8/LocalUserPresenceData.hpp>
#include <engine/iw8/mapInfo.hpp>
#include <engine/iw8/XUID.hpp>
#include <engine/iw8/enums/DWOnlineStatus.hpp>
#include <engine/iw8/unknown/bnet_class.hpp>

namespace functions {
	using CL_GetLocalClientSignInStateT = int(int controller_index);
	using Com_GameInfo_GetGameTypeForInternalNameT = iw8::gameTypeInfo*(const char* game_type_name);
	using Com_GameInfo_GetMapInfoForLoadNameT = iw8::mapInfo*(const char* map_name);
	using Dvar_FindVarByNameT = iw8::dvar_t*(const char* dvar_name);
	using Dvar_GetIntSafeT = int(const char* dvar_name);
	using Dvar_GetStringSafeT = const char*(const char* dvar_name);
	using Dvar_RegisterBoolT = iw8::dvar_t*(const char* dvar_name, bool value, std::uint32_t flags, const char* description);
	using dwGetLogOnStatusT = iw8::DWOnlineStatus(int controller_index);
	using Live_IsUserSignedInToDemonwareT = bool(int controller_index);
	using R_EndFrameT = void();
	using SEH_StringEd_GetStringT = const char*(const char* psz_reference);
	using unk_IsUserSignedInToBnetT = bool();
}
