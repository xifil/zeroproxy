#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	class ScriptStringList {
	public:
		int count_;				// 0x0000
		bool loaded_;			// 0x0004
	private:
		char pad_0005[0x0003];	// 0x0005
	public:
		const char** strings_;	// 0x0008
	};
	ENGINE_ASSERT_SZ(ScriptStringList, 0x0010);
}
