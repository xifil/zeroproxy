#pragma once
#include "common.hpp"

#include <engine/t7s/ClientGameState.hpp>
#include <engine/t7s/Font_s.hpp>
#include <engine/t7s/GamePad.hpp>
#include <engine/t7s/vec3_t.hpp>
#include <engine/t7s/enums/scriptInstance_t.hpp>
#include <engine/t7s/unknown/pad_handle_lookup.hpp>

namespace functions {
	using CL_GetKeyBindingInternalT = int(int local_client_num, const char* command, char** key_names, int game_pad_only, int bind_num);
	using Com_Frame_Try_Block_FunctionT = void();
	using Com_PrintMessageT = void(int channel, int console_type, const char* message, int unk);
	using Content_DoWeHaveContentPackT = bool();
	using Content_GetAvailableContentPacksT = std::uint64_t(char a1);
	using Content_HasEntitlementOwnershipByRefT = bool();
	using CScrCmd_SetAllControllersLightbarColorT = void(std::uint32_t control);
	using FS_FindXZoneT = const char*(const char* file_name);
	using GPad_ResetLightbarColorT = void();
	using GPad_SetLightbarColorT = void(int controller_index, t7s::vec3_t* color);
	using MSStore_OwnsContentT = bool();
	using R_AddCmdDrawTextWithCursorInternalT = void(const char* text, int max_chars, t7s::Font_s* font, float x, float y, float w, float x_scale, float y_scale,
		float rotation, const float* color, int style, int cursorPos, char cursor, float padding);
	using Scr_GetIntT = int(t7s::scriptInstance_t inst, std::uint32_t index);
	using SND_EndFrameT = void();
	using unk_GenericACFunctionT = void();
	using unk_InitSysDvarsT = void();
	using unk_WaitForObjectsT = std::int64_t();
}
