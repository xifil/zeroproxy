#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/XAssetHeader.hpp"
#include "engine/iw8/enums/XAssetType.hpp"

namespace iw8 {
	class XAsset {
	public:
		XAssetType type_;		// 0x0000
	private:
		char pad_0004[0x0004];	// 0x0004
	public:
		XAssetHeader header_;	// 0x0008
	};
	ENGINE_ASSERT_SZ(XAsset, 0x0010);
}
