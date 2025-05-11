#pragma once
#include "engine/engine_common.hpp"

namespace uwp {
	class XTaskQueueRegistrationToken {
	public:
		std::uint64_t token_;	// 0x0000
	};
	ENGINE_ASSERT_SZ(XTaskQueueRegistrationToken, 0x0008);
}
