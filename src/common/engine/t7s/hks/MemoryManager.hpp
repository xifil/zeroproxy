#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/ChunkList.hpp"
#include "engine/t7s/hks/enums/ChunkColor.hpp"

namespace t7s::hks {
	class MemoryManager {
	public:
		lua_Alloc allocator_;			// 0x0000
		void* allocator_ud_;			// 0x0008
		ChunkColor chunk_color;			// 0x0010
	private:
		char pad_0014[0x0004];			// 0x0014
	public:
		std::size_t used_;				// 0x0018
		std::size_t high_watermark_;	// 0x0020
		ChunkList allocation_list_;		// 0x0028
		ChunkList sweep_list_;			// 0x0038
		ChunkHeader* last_kept_chunk_;	// 0x0048
		lua_State* state_;				// 0x0050
	};
	ENGINE_ASSERT_SZ(MemoryManager, 0x0058);
}
