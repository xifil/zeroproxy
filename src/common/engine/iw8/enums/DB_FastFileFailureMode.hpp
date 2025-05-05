#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	enum class DB_FastFileFailureMode : std::int32_t {
		REQUIRED = 0x0,
		ALLOW_MISSING = 0x1
	};
}
