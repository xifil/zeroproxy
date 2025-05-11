#pragma once
#include "engine/engine_common.hpp"
#include "engine/uwp/IStoreImpl5.hpp"

namespace uwp {
	class IStoreImpl6 : public IStoreImpl5 {
	public:
		virtual HRESULT XStoreShowGiftingUIAsync(const XStoreContextHandle store_context_handle, const char* store_id, const char* name,
			const char* extended_json_data, XAsyncBlock* async) = 0;
		virtual HRESULT XStoreShowGiftingUIResult(XAsyncBlock* async) = 0;
	};
	ENGINE_ASSERT_SZ(IStoreImpl6, 0x0008);
}
