#pragma once
#include "common.hpp"
#include "game/function_types.hpp"

namespace game {
	void init();

	inline functions::CL_DrawScreenT* CL_DrawScreen{};
	inline functions::R_AddCmdDrawTextWithCursorInternalT* R_AddCmdDrawTextWithCursorInternal{};

	inline t6s::CachedAssets_t* sharedUiInfo_assets{};

	namespace sp {
		inline t6s::sp::CachedAssets_t* sharedUiInfo_assets{};
	}

	bool is_server();
}
