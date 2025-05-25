#pragma once
#include "common.hpp"
#include "game/function_types.hpp"

namespace game {
	void init();

	bool is_server();

	// Functions
	inline functions::AddBaseDrawTextCmdT* AddBaseDrawTextCmd{};
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
	inline functions::lua_getfieldT* lua_getfield{};
	inline functions::lua_pushbooleanT* lua_pushboolean{};
	inline functions::lua_pushstringT* lua_pushstring{};
	inline functions::lua_removeT* lua_remove{};
	inline functions::luaL_openlibT* luaL_openlib{};
	inline functions::LuaShared_PCallT* LuaShared_PCall{};
	inline functions::LUI_OpenMenuT* LUI_OpenMenu{};
	inline functions::R_EndFrameT* R_EndFrame{};
	inline functions::SEH_StringEd_GetStringT* SEH_StringEd_GetString{};
	inline functions::SV_Cmd_ArgvT* SV_Cmd_Argv{};
	inline functions::SV_UpdateUserinfo_fT* SV_UpdateUserinfo_f{};
	inline functions::unk_IsUnsupportedGPUT* unk_IsUnsupportedGPU{};
	inline functions::unk_IsUserSignedInToBNetT* unk_IsUserSignedInToBNet{};

	// Fields
	inline iw8::lua_State** LUI_luaVM{};
	inline bool* s_isContentEnumerationFinished{};
	inline bool* s_luaInFrontend{};
	inline iw8::LocalUserPresenceData(*s_presenceData)[8]{};
	inline iw8::CachedAssets_t* sharedUiInfo_assets{};
	inline int* unk_SignInState{};
	inline std::uint64_t* unk_XUIDCheck1{};
	inline std::uint64_t* unk_XUIDCheck2{};
	inline iw8::bnet_class* unk_BNetClass{};

	inline void LUI_CoD_LuaCall_ExecNow(iw8::lua_State* lua_vm, const char* str) {
		lua_getfield(lua_vm, -10002, "Engine");
		lua_getfield(lua_vm, -1, "DAGFFDGFII");
		lua_remove(lua_vm, -2);
		lua_pushstring(lua_vm, str);
		LuaShared_PCall(lua_vm, 1, 1);
	}

	inline void Cbuf_AddText(const char* cmd) {
		if (LUI_luaVM && *LUI_luaVM) {
			LUI_CoD_LuaCall_ExecNow(*LUI_luaVM, cmd);
		}
	}

	inline void R_AddCmdDrawText(const char* text, int max_chars, iw8::GfxFont* font, int font_height, float x, float y, float x_scale, float y_scale,
		float rotation, const iw8::vec4_t* color)
	{
		if (AddBaseDrawTextCmd != nullptr) {
			AddBaseDrawTextCmd(text, max_chars, font, nullptr, font_height, x, y, x_scale, y_scale, '\0', rotation, color, -1, '\0', nullptr, false, 0, 0,
				nullptr, false);
		}
	}
}
