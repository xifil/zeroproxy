#pragma once
#include "engine/engine_common.hpp"
#include "engine/uwp/IStoreImpl2.hpp"

namespace uwp {
	class IStoreImpl3 : public IStoreImpl2 {
	public:
		virtual HRESULT XStoreAcquireLicenseForDurablesAsync(const XStoreContextHandle store_context_handle, const char* store_id, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreAcquireLicenseForDurablesResult(XAsyncBlock* async, XStoreLicenseHandle* store_license_handle) = 0;
	};
	ENGINE_ASSERT_SZ(IStoreImpl3, 0x0008);
}
