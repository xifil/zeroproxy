#pragma once
#include "common.hpp"
#include "game/function_types.hpp"

namespace game {
	void init();

	inline functions::SEH_StringEd_GetStringT* SEH_StringEd_GetString{};
	inline functions::XStoreQueryGameLicenseResultT* XStoreQueryGameLicenseResult{};

	bool is_server();
}
