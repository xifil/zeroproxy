#pragma once
#include "engine/engine_common.hpp"
#include "engine/uwp/XStorePrice.hpp"
#include "engine/uwp/XStoreSku.hpp"
#include "engine/uwp/XStoreVideo.hpp"
#include "engine/uwp/enums/XUserAddOptions.hpp"

namespace uwp {
	class XStoreProduct {
	public:
		const char* store_id_;				// 0x0000
		const char* title_;					// 0x0008
		const char* description_;			// 0x0010
		const char* language_;				// 0x0018
		const char* in_app_offer_token_;	// 0x0020
		char* link_uri_;					// 0x0028
		XStoreProductKind product_kind_;	// 0x0030
	private:
		char pad_0034[0x0004];				// 0x0034
	public:
		XStorePrice price_;					// 0x0038
		bool has_digital_download_;			// 0x0090
		bool is_in_user_collection_;		// 0x0091
	private:
		char pad_0092[0x0002];				// 0x0092
	public:
		std::uint32_t keywords_count_;		// 0x0094
		const char** keywords_;				// 0x0098
		std::uint32_t skus_count_;			// 0x00A0
	private:
		char pad_00A4[0x0004];				// 0x00A4
	public:
		XStoreSku* skus_;					// 0x00A8
		std::uint32_t images_count_;		// 0x00B0
	private:
		char pad_00B4[0x0004];				// 0x00B4
	public:
		XStoreImage* images_;				// 0x00B8
		std::uint32_t videos_count_;		// 0x00C0
	private:
		char pad_00C4[0x0004];				// 0x00C4
	public:
		XStoreVideo* videos_;				// 0x00C8
	};
	ENGINE_ASSERT_SZ(XStoreProduct, 0x00D0);

	using XStoreProductQueryCallback = bool(const XStoreProduct* product, void* context);
}
