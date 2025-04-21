#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/XModelPiece.hpp"

namespace t6 {
	class XModelPieces {
	public:
		const char* name_;		// 0x0000
		int num_pieces_;		// 0x0004
		XModelPiece* pieces_;	// 0x0008
	};
	ENGINE_ASSERT_SZ(XModelPieces, 0x000C);
}
