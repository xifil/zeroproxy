#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	class GCRef {
	public:
		std::uint64_t gc_ptr_64_;	// 0x0000
	};
	ENGINE_ASSERT_SZ(GCRef, 0x0008);
}
