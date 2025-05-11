#pragma once
#include "engine/engine_common.hpp"

namespace uwp {
	enum class XUserAddOptions : std::int32_t {
		None = 0,
		AddDefaultUserSilently = 1,
		AllowGuests = 2,
		AddDefaultUserAllowingUI = 4
	};

	using XErrorOptions = XUserAddOptions;
	using XGameStreamingGamepadPhysicality = XUserAddOptions;
	using XGameUiTextEntryChangeTypeFlags = XUserAddOptions;
	using XGameUiWebAuthenticationOptions = XUserAddOptions;
	using XStoreProductKind = XUserAddOptions;
	using XUserGetTokenAndSignatureOptions = XUserAddOptions;
	using XUserPrivilegeOptions = XUserAddOptions;
}
