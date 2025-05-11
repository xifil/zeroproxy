#pragma once
#include "engine/engine_common.hpp"
#include "engine/uwp/enums/XStoreCanLicenseStatus.hpp"

namespace uwp {
	class XStoreCanAcquireLicenseResult {
	public:
		char licensable_sku_[5];		// 0x0000
	private:
		char pad_0005[0x0003];			// 0x0005
	public:
		XStoreCanLicenseStatus status_;	// 0x0008
	};
	ENGINE_ASSERT_SZ(XStoreCanAcquireLicenseResult, 0x000C);
}
