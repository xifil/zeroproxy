#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	class MRef {
	public:
		std::uint64_t ptr_64_;	// 0x0000
	};
	ENGINE_ASSERT_SZ(MRef, 0x0008);
}
