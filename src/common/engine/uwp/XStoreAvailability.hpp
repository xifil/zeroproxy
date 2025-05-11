#pragma once
#include "engine/engine_common.hpp"
#include "engine/uwp/XStorePrice.hpp"

namespace uwp {
	class XStoreAvailability {
	public:
		const char* availability_id_;	// 0x0000
		XStorePrice price_;				// 0x0008
		std::int64_t end_date_;			// 0x0060
	};
	ENGINE_ASSERT_SZ(XStoreAvailability, 0x0068);
}
