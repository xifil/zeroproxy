#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/ChunkHeader.hpp"
#include "engine/t7s/hks/DebugInfo.hpp"
#include "engine/t7s/hks/InstructionArray.hpp"
#include "engine/t7s/hks/MethodArray.hpp"
#include "engine/t7s/hks/ObjectArray.hpp"

namespace t7s::hks {
	class Method : public ChunkHeader {
	public:
		std::uint32_t hash_;			// 0x0010
		std::uint16_t num_upvals_;		// 0x0014
		std::uint16_t num_registers_;	// 0x0016
		std::uint8_t num_params_;		// 0x0018
		std::uint8_t flags_;			// 0x0019
	private:
		char pad_001A[0x0006];			// 0x001A
	public:
		InstructionArray instructions_;	// 0x0020
		ObjectArray constants_;			// 0x0030
		MethodArray children_;			// 0x0040
		DebugInfo* debug_;				// 0x0050
	};
	ENGINE_ASSERT_SZ(Method, 0x0058);
}
