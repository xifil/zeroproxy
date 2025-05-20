#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/ChunkHeader.hpp"
#include "engine/t7s/hks/MethodCache.hpp"

namespace t7s::hks {
	class Closure : public ChunkHeader {
	public:
		Method* method_;					// 0x0010
		HashTable* env_;					// 0x0018
		std::uint8_t may_have_upvalues_;	// 0x0020
	private:
		char pad_0021[0x0007];				// 0x0021
	public:
		MethodCache cache_;					// 0x0028
		UpValue* upvalues_[1];				// 0x0040
	};
	ENGINE_ASSERT_SZ(Closure, 0x0048);
}
