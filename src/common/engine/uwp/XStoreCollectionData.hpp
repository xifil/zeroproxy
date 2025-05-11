#pragma once
#include "engine/engine_common.hpp"

namespace uwp {
	class XStoreCollectionData {
	public:
		std::int64_t acquired_date_;					// 0x0000
		std::int64_t start_date_;						// 0x0008
		std::int64_t end_date_;							// 0x0010
		bool is_trial_;									// 0x0018
	private:
		char pad_0019[0x0003];							// 0x0019
	public:
		std::uint32_t trial_time_remaining_in_seconds_;	// 0x001C
		std::uint32_t quantity_;						// 0x0020
	private:
		char pad_0024[0x0004];							// 0x0024
	public:
		const char* campaign_id_;						// 0x0028
		const char* developer_offer_id_;				// 0x0030
	};
	ENGINE_ASSERT_SZ(XStoreCollectionData, 0x0038);
}
