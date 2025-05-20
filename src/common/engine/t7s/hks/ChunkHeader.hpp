#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/GenericChunkHeader.hpp"

namespace t7s::hks {
	class ChunkHeader : public GenericChunkHeader {
	public:
		ChunkHeader* next_;	// 0x0008
	};
	ENGINE_ASSERT_SZ(ChunkHeader, 0x0010);
}
