#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/ChunkHeader.hpp"

namespace t7s::hks {
	class ChunkList {
	public:
		ChunkHeader head_;	// 0x0000
	};
	ENGINE_ASSERT_SZ(ChunkList, 0x0010);
}
