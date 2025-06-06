﻿#pragma once
#include "common.hpp"
#include "game/function_types.hpp"

namespace game {
	void init();

	inline functions::bdLogMessageT* bdLogMessage{};
	inline functions::CL_DrawTextPhysicalT* CL_DrawTextPhysical{};
	inline functions::Cmd_AddCommandInternalT* Cmd_AddCommandInternal{};
	inline functions::Com_Frame_Try_Block_FunctionT* Com_Frame_Try_Block_Function{};
	inline functions::G_Glass_UpdateT* G_Glass_Update{};
	inline functions::ScrPlace_EndFrameT* ScrPlace_EndFrame{};
	inline functions::SEH_StringEd_GetStringT* SEH_StringEd_GetString{};
	inline functions::UI_RefreshFullscreenT* UI_RefreshFullscreen{};

	inline iw4s::CachedAssets_t* sharedUiInfo_assets{};

	bool is_server();
	bool should_enable_demonware_emulator();
}
