#pragma once
#include "engine/engine_common.hpp"
#include "engine/uwp/IStoreImpl3.hpp"

namespace uwp {
	class IStoreImpl4 : public IStoreImpl3 {
	public:
		virtual HRESULT XStoreShowAssociatedProductsUIAsync(const XStoreContextHandle store_context_handle, const char* store_id, XStoreProductKind product_kinds,
			XAsyncBlock* async) = 0;
		virtual HRESULT XStoreShowAssociatedProductsUIResult(XAsyncBlock* async) = 0;
		virtual HRESULT XStoreShowProductPageUIAsync(const XStoreContextHandle store_context_handle, const char* store_id, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreShowProductPageUIResult(XAsyncBlock* async) = 0;
	};
	ENGINE_ASSERT_SZ(IStoreImpl4, 0x0008);
}
