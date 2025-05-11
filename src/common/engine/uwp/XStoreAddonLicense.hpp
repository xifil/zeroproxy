#pragma once
#include "engine/engine_common.hpp"

namespace uwp {
	class XStoreAddonLicense {
	public:
		char sku_store_id_[18];			// 0x0000
		char in_app_offer_token_[64];	// 0x0012
		bool is_active_;				// 0x0052
	private:
		char pad_0053[0x0005];			// 0x0053
	public:
		std::int64_t expiration_date_;	// 0x0058
	};
	ENGINE_ASSERT_SZ(XStoreAddonLicense, 0x0060);
}
