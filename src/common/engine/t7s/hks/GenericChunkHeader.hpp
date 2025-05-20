#pragma once
#include "engine/engine_common.hpp"

namespace t7s::hks {
	class GenericChunkHeader {
	public:
		std::size_t flags_;	// 0x0000
	};
	ENGINE_ASSERT_SZ(GenericChunkHeader, 0x0008);
}
