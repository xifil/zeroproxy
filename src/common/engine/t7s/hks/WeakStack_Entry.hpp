#pragma once
#include "engine/engine_common.hpp"

namespace t7s::hks {
	class WeakStack_Entry {
	public:
		int weakness_;			// 0x0000
	private:
		char pad_0004[0x0004];	// 0x0004
	public:
		HashTable* table_;		// 0x0008
	};
	ENGINE_ASSERT_SZ(WeakStack_Entry, 0x0010);
}
