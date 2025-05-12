#pragma once
#include "engine/engine_common.hpp"

namespace uwp {
	class XStoreGameLicense {
	public:
		char sku_store_id_[18 /* STORE_SKU_ID_SIZE */];				// 0x0000
		bool is_active_;											// 0x0012
		bool is_trial_owned_by_this_user_;							// 0x0013
		bool is_disc_license_;										// 0x0014
		bool is_trial_;												// 0x0015
	private:
		char pad_0016[0x0002];										// 0x0016
	public:
		std::uint32_t trial_time_remaining_in_seconds_;				// 0x0018
		char trial_unique_id_[64 /* TRIAL_UNIQUE_ID_MAX_SIZE */];	// 0x001C
	private:
		char pad_005C[0x0004];										// 0x005C
	public:
		time_t expiration_date_;									// 0x0060
	};
	ENGINE_ASSERT_SZ(XStoreGameLicense, 0x0068);
}
