#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/LUIPoolUserData.hpp"

namespace t7s {
	class OpenedMenuData {
	public:
		int name_hash_;								// 0x0000
		LUIPoolUserData menu_element_pool_data_;	// 0x0004
		char name_[0x20];							// 0x0008
	};
	ENGINE_ASSERT_SZ(OpenedMenuData, 0x0028);
}
