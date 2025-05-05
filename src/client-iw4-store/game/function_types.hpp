#pragma once
#include "common.hpp"

#include <engine/iw4/cmd_function_s.hpp>
#include <engine/uwp/XStoreGameLicense.hpp>

namespace functions {
	using Cmd_AddCommandInternalT = void(const char* cmd_name, void(*function)(), iw4::cmd_function_s* alloced_cmd);
	using SEH_StringEd_GetStringT = const char*(const char* psz_reference);
	using XStoreQueryGameLicenseResultT = HRESULT(void* async, uwp::XStoreGameLicense* license);
}
