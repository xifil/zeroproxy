#pragma once
#include "common.hpp"

#include <engine/uwp/XStoreGameLicense.hpp>

namespace functions {
	using SEH_StringEd_GetStringT = const char*(const char* psz_reference);
	using XStoreQueryGameLicenseResultT = HRESULT(void* async, uwp::XStoreGameLicense* license);
}
