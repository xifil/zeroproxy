#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class GfxImageLoadDef {
	public:
		std::uint8_t level_count_;	// 0x0000
		std::uint8_t flags_;		// 0x0001
	private:
		char pad_0002[0x0002];		// 0x0002
	public:
		int format_;				// 0x0004
		int resource_size_;			// 0x0008
		std::uint8_t m_Data[1];		// 0x000C
	private:
		char pad_000D[0x0003];		// 0x000D
	};
	ENGINE_ASSERT_SZ(GfxImageLoadDef, 0x0010);
}
