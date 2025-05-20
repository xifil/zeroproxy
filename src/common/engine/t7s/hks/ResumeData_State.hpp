#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/ResumeData_Header.hpp"
#include "engine/t7s/hks/enums/GCResumePhase.hpp"

namespace t7s::hks {
	class ResumeData_State {
	public:
		ResumeData_Header h_;	// 0x0000
	private:
		char pad_0004[0x0004];	// 0x0004
	public:
		lua_State* state_;		// 0x0008
		GCResumePhase phase_;	// 0x0010
	private:
		char pad_0014[0x0004];	// 0x0014
	public:
		UpValue* pending_;		// 0x0018
	};
	ENGINE_ASSERT_SZ(ResumeData_State, 0x0020);
}
