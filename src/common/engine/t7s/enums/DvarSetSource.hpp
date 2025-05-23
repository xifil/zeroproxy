#pragma once
#include "engine/engine_common.hpp"

namespace t7s {
	enum class DvarSetSource {
		DVAR_SOURCE_INTERNAL = 0,
		DVAR_SOURCE_EXTERNAL = 1,
		DVAR_SOURCE_SCRIPT = 2,
		DVAR_SOURCE_DEVGUI = 3
	};
}
