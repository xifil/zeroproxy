#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/Object.hpp"

namespace t7s::hks {
	class ObjectArray {
	public:
		std::uint32_t size_;	// 0x0000
	private:
		char pad_0004[0x0004];	// 0x0004
	public:
		Object* data_;			// 0x0008
	};
	ENGINE_ASSERT_SZ(ObjectArray, 0x0010);
}
