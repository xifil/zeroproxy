#pragma once
#include "common.hpp"
#include "game/function_types.hpp"

#define LUA_REGISTRYINDEX	(-10000)
#define LUA_ENVIRONINDEX	(-10001)
#define LUA_GLOBALSINDEX	(-10002)

namespace game {
	void init();

	inline functions::CL_GetKeyBindingInternalT* CL_GetKeyBindingInternal{};
	inline functions::Com_Frame_Try_Block_FunctionT* Com_Frame_Try_Block_Function{};
	inline functions::Com_PrintMessageT* Com_PrintMessage{};
	inline functions::Content_DoWeHaveContentPackT* Content_DoWeHaveContentPack{};
	inline functions::Content_GetAvailableContentPacksT* Content_GetAvailableContentPacks{};
	inline functions::Content_HasEntitlementOwnershipByRefT* Content_HasEntitlementOwnershipByRef{};
	inline functions::CScrCmd_SetAllControllersLightbarColorT* CScrCmd_SetAllControllersLightbarColor{};
	inline functions::FS_FindXZoneT* FS_FindXZone{};
	inline functions::GPad_ResetLightbarColorT* GPad_ResetLightbarColor{};
	inline functions::GPad_SetLightbarColorT* GPad_SetLightbarColor{};
	inline functions::hks_obj_tolstringT* hks_obj_tolstring{};
	inline functions::hksI_openlibT* hksI_openlib{};
	inline functions::Key_KeynumToNameT* Key_KeynumToName{};
	inline functions::lua_pcallT* lua_pcall{};
	inline functions::lua_pushlstringT* lua_pushlstring{};
	inline functions::lua_pushvfstringT* lua_pushvfstring{};
	inline functions::lua_setfieldT* lua_setfield{};
	inline functions::lua_tobooleanT* lua_toboolean{};
	inline functions::lua_topointerT* lua_topointer{};
	inline functions::MSStore_OwnsContentT* MSStore_OwnsContent{};
	inline functions::R_AddCmdDrawTextWithCursorInternalT* R_AddCmdDrawTextWithCursorInternal{};
	inline functions::Scr_GetIntT* Scr_GetInt{};
	inline functions::SND_EndFrameT* SND_EndFrame{};
	inline functions::unk_GenericACFunctionT* unk_AC_OnDllLoaded{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk2_Threaded{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk3{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk4{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk5{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk6{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk7{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk8{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk10{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk11{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk13_Threaded{};
	inline functions::unk_InitSysDvarsT* unk_InitSysDvars{};
	inline functions::unk_WaitForObjectsT* unk_WaitForObjects{};

	inline t7s::ClientGameState* clientGameStates{};
	inline int* com_quitInProgress{};
	inline int* s_contentPackMetaData{};
	inline t7s::GamePad* s_gamePads{};
	inline std::uint64_t* unk_AC_State{};
	inline t7s::keyNumToNameMapping_t* unk_KeyNumToName{};
	inline std::uint8_t* unk_OwnedContent{};
	inline t7s::pad_handle_lookup* unk_PadHandles{};
	inline t7s::Font_s* unk_WatermarkFont{};

	bool is_server();

	int Com_LocalClient_GetControllerIndex(int local_client_num);
	void lua_pop(t7s::lua_State* s, int n);
	void lua_pushboolean(t7s::lua_State* s, int b);
	void lua_pushinteger(t7s::lua_State* s, int n);
	void lua_pushnil(t7s::lua_State* s);
	void lua_pushnumber(t7s::lua_State* s, float n);
	void lua_pushfstring(t7s::lua_State* s, const char* fmt, ...);
	void lua_pushvalue(t7s::lua_State* s, int index);
	void lua_setglobal(t7s::lua_State* s, const char* k);
	const char* lua_tostring(t7s::lua_State* s, int index);
	float lua_tonumber(t7s::lua_State* s, int index);
	void luaL_register(t7s::lua_State* s, const char* lib_name, const t7s::luaL_Reg* l);

	namespace extra {
		t7s::hks::Object get_object_for_index(t7s::lua_State* s, int index);
	}
}
