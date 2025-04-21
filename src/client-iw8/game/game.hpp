#pragma once
#include "common.hpp"
#include "game/function_types.hpp"

namespace game {
	void init();

	bool is_server();

	// Functions
	inline functions::Com_GameInfo_GetGameTypeForInternalNameT* Com_GameInfo_GetGameTypeForInternalName{};
    inline functions::Com_GameInfo_GetMapInfoForLoadNameT* Com_GameInfo_GetMapInfoForLoadName{};
    inline functions::Dvar_GetIntSafeT* Dvar_GetIntSafe{};
    inline functions::Dvar_GetStringSafeT* Dvar_GetStringSafe{};
	inline functions::R_EndFrameT* R_EndFrame{};
	inline functions::SEH_StringEd_GetStringT* SEH_StringEd_GetString{};

	// Fields
	inline bool* s_luaInFrontend{};
}
