#pragma once
#include "engine/engine_common.hpp"

namespace t7s::hks {
	enum class BytecodeSharingFormat {
		BYTECODE_DEFAULT = 0,
		BYTECODE_INPLACE = 1,
		BYTECODE_REFERENCED = 2
	};
}
