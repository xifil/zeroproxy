#pragma once
#include "engine/engine_common.hpp"

namespace uwp {
	class XStoreRateAndReviewResult {
	public:
		bool was_updated_;	// 0x0000
	};
	ENGINE_ASSERT_SZ(XStoreRateAndReviewResult, 0x0001);
}
