#pragma once
#include "engine/engine_common.hpp"

namespace uwp {
	class XStoreConsumableResult {
	public:
		std::uint32_t quantity_;	// 0x0000
	};
	ENGINE_ASSERT_SZ(XStoreConsumableResult, 0x0004);
}
