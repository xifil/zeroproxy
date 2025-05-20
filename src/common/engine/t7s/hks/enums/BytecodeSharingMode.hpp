#pragma once
#include "engine/engine_common.hpp"

namespace t7s::hks {
	enum class BytecodeSharingMode : std::int64_t {
		HKS_BYTECODE_SHARING_OFF = 0,
		HKS_BYTECODE_SHARING_ON = 1,
		HKS_BYTECODE_SHARING_SECURE = 2
	};
}
