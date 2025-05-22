#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/LocalizeEntry.hpp"

namespace t7s {
	union XAssetHeader {
		LocalizeEntry* localize_;
		void* data_;
	};
}
