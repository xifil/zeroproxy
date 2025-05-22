#pragma once
#include "common.hpp"

#include <engine/t7s/ClientGameState.hpp>
#include <engine/t7s/Font_s.hpp>
#include <engine/t7s/GamePad.hpp>
#include <engine/t7s/keyNumToNameMapping_t.hpp>
#include <engine/t7s/lua_State.hpp>
#include <engine/t7s/luaL_Reg.hpp>
#include <engine/t7s/vec3_t.hpp>
#include <engine/t7s/XAssetHeader.hpp>
#include <engine/t7s/enums/scriptInstance_t.hpp>
#include <engine/t7s/enums/XAssetType.hpp>
#include <engine/t7s/hks/CClosure.hpp>
#include <engine/t7s/unknown/pad_handle_lookup.hpp>

namespace functions {
	using Cinematic_StartPlaybackT = void(const char* name, const char* key, const std::uint32_t playback_flags, const float volume, void* callback_info,
		const int id);
	using CL_GetKeyBindingInternalT = int(int local_client_num, const char* command, char** key_names, int game_pad_only, int bind_num);
	using Com_Frame_Try_Block_FunctionT = void();
	using Com_PrintMessageT = void(int channel, int console_type, const char* message, int unk);
	using Content_DoWeHaveContentPackT = bool();
	using Content_GetAvailableContentPacksT = std::uint64_t(char a1);
	using Content_HasEntitlementOwnershipByRefT = bool();
	using CScrCmd_SetAllControllersLightbarColorT = void(std::uint32_t control);
	using DB_FindXAssetHeaderT = t7s::XAssetHeader(t7s::XAssetType type, const char* name, bool error_if_missing, int wait_time);
	using FS_FindXZoneT = const char*(const char* file_name);
	using GPad_ResetLightbarColorT = void();
	using GPad_SetLightbarColorT = void(int controller_index, t7s::vec3_t* color);
	using hks_obj_tolstringT = const char*(t7s::lua_State* s, t7s::hks::Object* obj, size_t* len);
	using hksI_openlibT = void(t7s::lua_State* s, const char* lib_name, const t7s::luaL_Reg l[], int n_up, int is_hks_func);
	using Key_KeynumToStringT = const char*(int local_client_num, int key_num, bool translate);
	using lua_pcallT = int(t7s::lua_State* s, long n_args, long n_results);
	using lua_pushlstringT = void(t7s::lua_State* s, const char* str, size_t l);
	using lua_pushvfstringT = const char*(t7s::lua_State* s, const char* fmt, va_list* arg_p);
	using lua_setfieldT = void(t7s::lua_State* s, int index, const char* k);
	using lua_tobooleanT = int(t7s::lua_State* s, int index);
	using lua_topointerT = const void*(t7s::lua_State* s, int index);
	using MSStore_OwnsContentT = bool();
	using R_AddCmdDrawTextWithCursorInternalT = void(const char* text, int max_chars, t7s::Font_s* font, float x, float y, float w, float x_scale, float y_scale,
		float rotation, const float* color, int style, int cursorPos, char cursor, float padding);
	using Scr_GetIntT = int(t7s::scriptInstance_t inst, std::uint32_t index);
	using SND_EndFrameT = void();
	using unk_GenericACFunctionT = void();
	using unk_InitSysDvarsT = void();
	using unk_WaitForObjectsT = std::int64_t();
}
