#pragma once
#include "common.hpp"

#include <engine/iw4/CachedAssets_t.hpp>
#include <engine/iw4/cmd_function_s.hpp>
#include <engine/iw4/Font_s.hpp>

namespace functions {
	using CL_DrawTextPhysicalT = void(const char* text, int max_chars, iw4::Font_s* font, float x, float y, float x_scale, float y_scale, const float* color,
		int style);
	using Cmd_AddCommandInternalT = void(const char* cmd_name, void(*function)(), iw4::cmd_function_s* alloced_cmd);
	using Com_Frame_Try_Block_FunctionT = void();
	using G_Glass_UpdateT = void();
	using ScrPlace_EndFrameT = void();
	using SEH_StringEd_GetStringT = const char*(const char* psz_reference);
	using UI_RefreshFullscreenT = void(std::uint32_t local_client_num);
}
