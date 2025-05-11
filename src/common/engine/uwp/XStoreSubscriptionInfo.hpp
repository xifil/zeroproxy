#pragma once
#include "engine/engine_common.hpp"
#include "engine/uwp/enums/XStoreDurationUnit.hpp"

namespace uwp {
	class XStoreSubscriptionInfo {
	public:
		bool has_trial_period_;						// 0x0000
	private:
		char pad_0001[0x0003];						// 0x0001
	public:
		XStoreDurationUnit trial_period_unit_;		// 0x0004
		std::uint32_t trial_period_;				// 0x0008
		XStoreDurationUnit billing_period_unit_;	// 0x000C
		std::uint32_t billing_period_;				// 0x0010
	};
	ENGINE_ASSERT_SZ(XStoreSubscriptionInfo, 0x0014);
}
