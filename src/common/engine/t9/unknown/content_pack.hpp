#pragma once
#include "engine/engine_common.hpp"

namespace t9 {
	class content_pack {
	private:
		char pad_0000[0x0014];	// 0x0000
	public:
		int var1_;				// 0x0014
	private:
		char pad_0018[0x0030];	// 0x0018
	public:
		int var2_;				// 0x0048
		int var3_;				// 0x004C
	private:
		char pad_0050[0x0080];
	};
	ENGINE_ASSERT_SZ(content_pack, 0x00D0);
}