#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	class bnet_class {
	public:
		int state_;				// 0x0000
	private:
		char pad_0004[0x02CC];	// 0x0004
	public:
		bool finished_auth_;	// 0x02D0
	private:
		char pad_02D1[0x0023];	// 0x02D1
	public:
		int var3_;				// 0x02F4
		char var4_;				// 0x02F8
	private:
		char pad_02F9[0x0003];	// 0x02F9
	public:
		int var5_;				// 0x02FC
	};
	ENGINE_ASSERT_SZ(bnet_class, 0x0300);
}
