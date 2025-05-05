#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/ScriptStringList.hpp"
#include "engine/iw8/XAsset.hpp"

namespace iw8 {
	class XAssetList {
	public:
		ScriptStringList string_list_;	// 0x0000
		std::uint32_t asset_count_;		// 0x0010
		std::uint32_t asset_read_pos_;	// 0x0014
		XAsset* assets_;				// 0x0018
	};
	ENGINE_ASSERT_SZ(XAssetList, 0x0020);
}
