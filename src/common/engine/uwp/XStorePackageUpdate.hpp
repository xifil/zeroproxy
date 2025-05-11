#pragma once
#include "engine/engine_common.hpp"

namespace uwp {
	class XStorePackageUpdate {
	public:
		char package_identifier_[0x21];	// 0x0000
		bool is_mandatory_;				// 0x0021
	};
	ENGINE_ASSERT_SZ(XStorePackageUpdate, 0x0022);
}
