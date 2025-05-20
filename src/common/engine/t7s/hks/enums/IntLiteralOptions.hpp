#pragma once
#include "engine/engine_common.hpp"

namespace t7s::hks {
	enum class IntLiteralOptions {
		INT_LITERALS_NONE = 0,
		INT_LITERALS_LUD = 1,
		INT_LITERALS_32BIT = 1,
		INT_LITERALS_UI64 = 2,
		INT_LITERALS_64BIT = 2,
		INT_LITERALS_ALL = 3
	};
}
