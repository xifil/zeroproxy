#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/ChunkHeader.hpp"
#include "engine/t7s/hks/Object.hpp"

namespace t7s::hks {
	class CClosure : public ChunkHeader {
	public:
		lua_CFunction function_;		// 0x0010
		HashTable* env_;				// 0x0018
		std::uint16_t num_upvalues_;	// 0x0020
		std::uint16_t flags_;			// 0x0022
	private:
		char pad_0024[0x0004];			// 0x0024
	public:
		InternString* name_;			// 0x0028
		Object upvalues_[1];			// 0x0030
	};
	ENGINE_ASSERT_SZ(CClosure, 0x0040);
}
