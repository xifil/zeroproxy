#pragma once
#include "engine/engine_common.hpp"

namespace t7s::hks {
	enum class BytecodeEndianness {
		HKS_BYTECODE_DEFAULT_ENDIAN = 0,
		HKS_BYTECODE_BIG_ENDIAN = 1,
		HKS_BYTECODE_LITLE_ENDIAN = 2
	};
}
