#pragma once
#include "common.hpp"

#include <engine/iw6s/CachedAssets_t.hpp>
#include <engine/iw6s/Font_s.hpp>

namespace functions {
	using Com_Frame_Try_Block_FunctionT = void();
	using LUI_OpenMenuT = void(int local_client_num, const char* menu_name, int is_popup, int is_modal, int is_exclusive);
	using R_AddCmdDrawTextT = void(const char* text, int max_chars, iw6s::Font_s* font, float x, float y, float x_scale, float y_scale, float rotation,
		const float* color, int style);
	using R_EndFrameT = void();
	using SEH_StringEd_GetStringT = const char*(const char* psz_reference);
}
