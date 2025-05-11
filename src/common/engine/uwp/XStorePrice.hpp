#pragma once
#include "engine/engine_common.hpp"

namespace uwp {
	class XStorePrice {
	public:
		float base_price_;						// 0x0000
		float price_;							// 0x0004
		float recurrence_price_;				// 0x0008
	private:
		char pad_000C[0x0004];					// 0x000C
	public:
		const char* currency_code_;				// 0x0010
		char formatted_base_price_[16];			// 0x0018
		char formatted_price_[16];				// 0x0028
		char formatted_recurrence_price_[16];	// 0x0038
		bool is_on_sale_;						// 0x0048
	private:
		char pad_0049[0x0007];					// 0x0049
	public:
		std::int64_t sale_end_date_;			// 0x0050
	};
	ENGINE_ASSERT_SZ(XStorePrice, 0x0058);
}
