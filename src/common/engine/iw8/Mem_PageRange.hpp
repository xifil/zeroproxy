#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/enums/Mem_PageID.hpp"

namespace iw8 {
	class Mem_PageRange {
	public:
		Mem_PageID first_page_id_;	// 0x0000
		Mem_PageID last_page_id_;	// 0x0004
	};
	ENGINE_ASSERT_SZ(Mem_PageRange, 0x0008);
}
