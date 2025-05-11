#pragma once
#include "engine/engine_common.hpp"

namespace uwp {
	class XAsyncBlock {
	public:
		XTaskQueueHandle queue_;		// 0x0000
		void* context_;					// 0x0008
		void(*callback_)(XAsyncBlock*);	// 0x0010
		std::uint8_t internal_[0x0020];	// 0x0018
	};
	ENGINE_ASSERT_SZ(XAsyncBlock, 0x0038);
}
