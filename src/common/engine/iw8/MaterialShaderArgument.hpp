#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/enums/MaterialArgumentType.hpp"

namespace iw8 {
	class MaterialShaderArgument {
	public:
		MaterialArgumentType type_;	// 0x0000
		std::uint8_t shader_;		// 0x0001
		std::uint16_t dest_;		// 0x0002
		std::uint16_t index_;		// 0x0004
	};
	ENGINE_ASSERT_SZ(MaterialShaderArgument, 0x0006);
}
