#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	class TTFDef {
	public:
		const char* name_;		// 0x0000
		int file_len_;			// 0x0008
	private:
		char pad_000C[0x0004];	// 0x000C
	public:
		const char* file_;		// 0x0010
		void* font_face_;		// 0x0018
	};
	ENGINE_ASSERT_SZ(TTFDef, 0x0020);
}
