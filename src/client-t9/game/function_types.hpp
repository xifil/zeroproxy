#pragma once
#include "common.hpp"

#include <engine/t9/dvar_t.hpp>
#include <engine/t9/Font_s.hpp>
#include <engine/t9/enums/DvarSetSource.hpp>
#include <engine/t9/enums/LobbyNetworkMode.hpp>
#include <engine/t9/unknown/content_manager.hpp>

namespace functions {
	using BB_AlertT = void(const char* type, const char* msg);
	using CL_DisconnectT = void(int local_client_num, bool deactivate_client, const char* message);
	using CL_DrawTextPhysicalT = void(const char* text, int max_chars, t9::Font_s* font, float x, float y, float rotation, float x_scale, float y_scale, const float* color, int style, int padding);
	using Com_GametypeSettings_SetGametypeT = void(const char* game_type, bool load_default_settings);
	using Com_SessionMode_SetNetworkModeT = void(int mode);
	using Dvar_FindVarT = t9::dvar_t*(std::int64_t dvar_hash);
	using Dvar_ResetT = void(t9::dvar_t* dvar, t9::DvarSetSource source);
	using Dvar_SetBoolFromSourceT = void(t9::dvar_t* dvar, bool value, t9::DvarSetSource source);
	using Dvar_SetIntFromSourceT = void(t9::dvar_t* dvar, int value, t9::DvarSetSource source);
	using Dvar_ShowOverStackT = void();
	using LiveUser_GetUserDataForControllerT = std::uintptr_t* (int controller_index);
	using LobbyBase_SetNetworkModeT = void(t9::LobbyNetworkMode network_mode);
	using LobbyData_SetMapT = void(int lobby_mode, const char* map_name);
	using LobbySession_GetControllingLobbySessionT = int(int lobby_module);
	using unk_SetScreenT = void(int screen, char a2);
	using unk_SetUsernameT = void(std::uintptr_t* _this, const char* username);
}
