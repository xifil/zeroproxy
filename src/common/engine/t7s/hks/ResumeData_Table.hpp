#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/ResumeData_Header.hpp"

namespace t7s::hks {
	class ResumeData_Table {
	public:
		ResumeData_Header h_;		// 0x0000
	private:
		char pad_0004[0x0004];		// 0x0004
	public:
		HashTable* table_;			// 0x0008
		std::uint32_t array_index_;	// 0x0010
		std::uint32_t hash_index_;	// 0x0014
		int weakness_;				// 0x0018
	private:
		char pad_001C[0x0004];		// 0x001C
	};
	ENGINE_ASSERT_SZ(ResumeData_Table, 0x0020);
}
