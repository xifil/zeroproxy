#pragma once
#include "common.hpp"

#include <engine/iw8/gameTypeInfo.hpp>
#include <engine/iw8/mapInfo.hpp>

namespace functions {
	using Com_GameInfo_GetGameTypeForInternalNameT = iw8::gameTypeInfo*(const char* game_type_name);
	using Com_GameInfo_GetMapInfoForLoadNameT = iw8::mapInfo*(const char* map_name);
	using Dvar_GetIntSafeT = int(const char* dvar_name);
	using Dvar_GetStringSafeT = const char*(const char* dvar_name);
	using R_EndFrameT = void();
	using SEH_StringEd_GetStringT = const char*(const char* psz_reference);
}
