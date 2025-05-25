#pragma once
#include "common.hpp"
#include "game/function_types.hpp"

namespace game {
	void init();

	bool is_server();

	// Functions
	inline functions::CL_GetLocalClientSignInStateT* CL_GetLocalClientSignInState{};
	inline functions::Com_GameInfo_GetGameTypeForInternalNameT* Com_GameInfo_GetGameTypeForInternalName{};
    inline functions::Com_GameInfo_GetMapInfoForLoadNameT* Com_GameInfo_GetMapInfoForLoadName{};
    inline functions::DB_FindXAssetHeaderT* DB_FindXAssetHeader{};
    inline functions::DB_LoadXFileT* DB_LoadXFile{};
    inline functions::Dvar_FindVarByNameT* Dvar_FindVarByName{};
    inline functions::Dvar_GetIntSafeT* Dvar_GetIntSafe{};
    inline functions::Dvar_GetStringSafeT* Dvar_GetStringSafe{};
    inline functions::Dvar_RegisterBoolT* Dvar_RegisterBool{};
    inline functions::dwGetLogOnStatusT* dwGetLogOnStatus{};
    inline functions::GamerProfile_SetDataByNameT* GamerProfile_SetDataByName{};
    inline functions::Info_ValueForKeyT* Info_ValueForKey{};
    inline functions::Live_IsUserSignedInToDemonwareT* Live_IsUserSignedInToDemonware{};
    inline functions::lua_pushbooleanT* lua_pushboolean{};
    inline functions::luaL_openlibT* luaL_openlib{};
	inline functions::R_EndFrameT* R_EndFrame{};
	inline functions::SEH_StringEd_GetStringT* SEH_StringEd_GetString{};
	inline functions::SV_Cmd_ArgvT* SV_Cmd_Argv{};
	inline functions::SV_UpdateUserinfo_fT* SV_UpdateUserinfo_f{};
	inline functions::unk_IsUnsupportedGPUT* unk_IsUnsupportedGPU{};
	inline functions::unk_IsUserSignedInToBNetT* unk_IsUserSignedInToBNet{};

	// Fields
	inline bool* s_isContentEnumerationFinished{};
	inline bool* s_luaInFrontend{};
	inline iw8::LocalUserPresenceData(*s_presenceData)[8]{};
	inline int* unk_SignInState{};
	inline std::uint64_t* unk_XUIDCheck1{};
	inline std::uint64_t* unk_XUIDCheck2{};
	inline iw8::bnet_class* unk_BNetClass{};
}
