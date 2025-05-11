#pragma once
#include "common.hpp"

#include <engine/t6s/CachedAssets_t.hpp>

namespace functions {
	using CL_DrawScreenT = void(std::uint32_t local_client_num);
	using DB_FindXAssetHeaderT = void*(int type, const char* name, bool error_if_missing, int wait_time);
	using R_AddCmdDrawTextWithCursorInternalT = void(const char* text, int max_chars, t6s::Font_s* font, float x, float y, float w, float x_scale, float y_scale,
		float rotation, const float* color, int style, int cursorPos, char cursor, float padding);
}
