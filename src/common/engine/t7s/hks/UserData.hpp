#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/ChunkHeader.hpp"

namespace t7s::hks {
	class UserData : public ChunkHeader {
	public:
		HashTable* env_;	// 0x0010
		Metatable* meta_;	// 0x0018
		char data_[8];		// 0x0020
	};
	ENGINE_ASSERT_SZ(UserData, 0x0028);
}
