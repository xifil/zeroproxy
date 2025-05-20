#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/ResumeData_Header.hpp"

namespace t7s::hks {
	class ResumeData_UserData {
	public:
		ResumeData_Header h_;	// 0x0000
	private:
		char pad_0004[0x0004];	// 0x0004
	public:
		UserData* data_;		// 0x0008
	};
	ENGINE_ASSERT_SZ(ResumeData_UserData, 0x0010);
}
