#pragma once
#include "engine/engine_common.hpp"
#include "engine/uwp/IStoreImpl1.hpp"

namespace uwp {
	class IStoreImpl2 : public IStoreImpl1 {
	public:
		virtual bool XStoreIsAvailabilityPurchasable(XStoreAvailability availability) = 0;
	};
	ENGINE_ASSERT_SZ(IStoreImpl2, 0x0008);
}
