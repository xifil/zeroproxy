#pragma once
#include "engine/engine_common.hpp"

namespace t7s::hks {
	class JmpBuf {
	public:
		void* jb_[12];	// 0x0000
	};
	ENGINE_ASSERT_SZ(JmpBuf, 0x0060);
}
