#pragma once
#include "engine/engine_common.hpp"

namespace uwp {
	enum class XStoreCanLicenseStatus : std::int32_t {
		NotLicensableToUser = 0,
		Licensable = 1,
		LicenseActionNotApplicableToProduct = 2
	};
}
