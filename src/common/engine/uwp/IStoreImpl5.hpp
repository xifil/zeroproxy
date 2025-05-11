#pragma once
#include "engine/engine_common.hpp"
#include "engine/uwp/IStoreImpl4.hpp"

namespace uwp {
	class IStoreImpl5 : public IStoreImpl4 {
	public:
		virtual HRESULT XStoreQueryAssociatedProductsForStoreIdAsync(const XStoreContextHandle store_context_handle, const char* store_product_id,
			XStoreProductKind product_kinds, std::uint32_t max_items_to_retrieve_per_page, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreQueryAssociatedProductsForStoreIdResult(XAsyncBlock* async, XStoreProductQueryHandle* product_query_handle) = 0;
		virtual HRESULT XStoreQueryPackageUpdatesAsync(const XStoreContextHandle store_context_handle, const char** package_identifiers,
			std::size_t package_identifiers_count, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreQueryPackageUpdatesResultCount(XAsyncBlock* async, std::uint32_t* count) = 0;
		virtual HRESULT XStoreQueryPackageUpdatesResult(XAsyncBlock* async, std::uint32_t count, XStorePackageUpdate* package_updates) = 0;
	};
	ENGINE_ASSERT_SZ(IStoreImpl5, 0x0008);
}
