#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	class DB_AuthSignature {
	public:
		std::uint8_t bytes_[256];	// 0x0000
	};
	ENGINE_ASSERT_SZ(DB_AuthSignature, 0x0100);
}
