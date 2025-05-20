#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/ChunkHeader.hpp"
#include "engine/t7s/hks/Object.hpp"

namespace t7s::hks {
	class UpValue : public ChunkHeader {
	public:
		Object storage_;	// 0x0010
		Object* loc_;		// 0x0020
		UpValue* next_;		// 0x0028
	};
	ENGINE_ASSERT_SZ(UpValue, 0x0030);
}
