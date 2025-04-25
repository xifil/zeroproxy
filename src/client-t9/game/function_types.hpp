#pragma once
#include "common.hpp"

#include <engine/t9/Font_s.hpp>
#include <engine/t9/enums/LobbyNetworkMode.hpp>
#include <engine/t9/unknown/content_manager.hpp>

namespace functions {
	using BB_AlertT = void(const char* type, const char* msg);
	using CL_DisconnectT = void(int local_client_num, bool deactivate_client, const char* message);
	using CL_DrawTextPhysicalT = void(const char* text, int max_chars, t9::Font_s* font, float x, float y, float rotation, float x_scale, float y_scale, const float* color, int style, int padding);
	using Com_SessionMode_SetNetworkModeT = void(int mode);
	using Dvar_SetBoolFromSourceT = void(std::uintptr_t* dvar, bool value, int source);
	using Dvar_ShowOverStackT = void();
	using LiveUser_GetUserDataForControllerT = std::uintptr_t* (int controller_index);
	using LobbyBase_SetNetworkModeT = void(t9::LobbyNetworkMode network_mode);
	using unk_SetScreenT = void(int screen, char a2);
	using unk_SetUsernameT = void(std::uintptr_t* _this, const char* username);
}
