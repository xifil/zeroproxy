#pragma once
#include "common.hpp"
#include "game/function_types.hpp"

namespace game {
	void init();

	inline functions::Com_Frame_Try_Block_FunctionT* Com_Frame_Try_Block_Function{};
	inline functions::LUI_OpenMenuT* LUI_OpenMenu{};
	inline functions::R_AddCmdDrawTextT* R_AddCmdDrawText{};
	inline functions::R_EndFrameT* R_EndFrame{};
	inline functions::SEH_StringEd_GetStringT* SEH_StringEd_GetString{};

	inline iw6::CachedAssets_t* sharedUiInfo_assets{};

	bool is_server();
}
