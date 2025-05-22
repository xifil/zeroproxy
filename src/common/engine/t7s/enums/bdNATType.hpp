#pragma once
#include "engine/engine_common.hpp"

namespace t7s {
	enum class bdNATType : std::uint8_t {
		BD_NAT_UNKNOWN = 0,
		BD_NAT_OPEN = 1,
		BD_NAT_MODERATE = 2,
		BD_NAT_STRICT = 3
	};
}
