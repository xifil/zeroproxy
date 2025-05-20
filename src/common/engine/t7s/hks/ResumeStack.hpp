#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/ResumeData_Entry.hpp"

namespace t7s::hks {
	class ResumeStack {
	public:
		ResumeData_Entry* storage_;		// 0x0000
		int num_entries_;				// 0x0008
		std::uint32_t num_allocated_;	// 0x000C
	};
	ENGINE_ASSERT_SZ(ResumeStack, 0x0010);
}
