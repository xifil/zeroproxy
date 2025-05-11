#pragma once
#include "engine/engine_common.hpp"
#include "engine/uwp/XStoreAvailability.hpp"
#include "engine/uwp/XStoreCollectionData.hpp"
#include "engine/uwp/XStorePrice.hpp"
#include "engine/uwp/XStoreSubscriptionInfo.hpp"
#include "engine/uwp/XStoreVideo.hpp"

namespace uwp {
	class XStoreSku {
	public:
		const char* sku_id_;						// 0x0000
		const char* title_;							// 0x0008
		const char* description_;					// 0x0010
		const char* language_;						// 0x0018
		XStorePrice price_;							// 0x0020
		bool is_trial_;								// 0x0078
		bool is_in_user_collection_;				// 0x0079
	private:
		char pad_007A[0x0006];						// 0x007A
	public:
		XStoreCollectionData collection_data_;		// 0x0080
		bool is_subscription_;						// 0x00B8
	private:
		char pad_00B9[0x0003];						// 0x00B9
	public:
		XStoreSubscriptionInfo subscription_info_;	// 0x00BC
		std::uint32_t bundled_skus_count_;			// 0x00D0
	private:
		char pad_00D4[0x0004];						// 0x00D4
	public:
		const char** bundled_skus_;					// 0x00D8
		std::uint32_t images_count_;				// 0x00E0
	private:
		char pad_00E4[0x0004];						// 0x00E4
	public:
		XStoreImage* images_;						// 0x00E8
		std::uint32_t videos_count_;				// 0x00F0
	private:
		char pad_00F4[0x0004];						// 0x00F4
	public:
		XStoreVideo* videos_;						// 0x00F8
		std::uint32_t availabilities_count_;		// 0x0100
	private:
		char pad_0104[0x0004];						// 0x0104
	public:
		XStoreAvailability* availabilities_;		// 0x0108
	};
	ENGINE_ASSERT_SZ(XStoreSku, 0x0110);
}
