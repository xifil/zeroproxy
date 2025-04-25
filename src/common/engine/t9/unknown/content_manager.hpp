#pragma once
#include "engine/engine_common.hpp"
#include "engine/t9/unknown/content_pack.hpp"

namespace t9 {
	class content_manager {
	private:
		char pad_0000[0x0008];			// 0x0000
	public:
		int pack_count_;				// 0x0008
	private:
		char pad_000C[0x0004];			// 0x000C
	public:
		content_pack* content_packs_;	// 0x0010
	};
	ENGINE_ASSERT_SZ(content_manager, 0x0018);
}