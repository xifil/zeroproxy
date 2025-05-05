#pragma once
#include "common.hpp"

#include <engine/uwp/XStoreGameLicense.hpp>

namespace functions {
	using DB_FindXAssetHeaderT = void*(int type, const char* name, bool error_if_missing, int wait_time);
	using XStoreQueryGameLicenseResultT = HRESULT(void* async, uwp::XStoreGameLicense* license);
}
