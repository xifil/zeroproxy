#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/GenericChunkHeader.hpp"

namespace t7s::hks {
	class InternString : GenericChunkHeader {
	public:
		std::size_t length_bits_;	// 0x0008
		std::uint32_t hash_;		// 0x0010
		char data_[0x1E];			// 0x0014
	private:
		char pad_0032[0x0006];		// 0x0032
	};
	ENGINE_ASSERT_SZ(InternString, 0x0038);
}
