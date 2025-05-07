#pragma once
#include "common.hpp"

#include <engine/uwp/XStoreGameLicense.hpp>

namespace functions {
	using LUI_OpenMenuT = void(int local_client_num, const char* menu_name, int is_popup, int is_modal, int is_exclusive);
	using SEH_StringEd_GetStringT = const char*(const char* psz_reference);
	using XStoreQueryGameLicenseResultT = HRESULT(void* async, uwp::XStoreGameLicense* license);
}
