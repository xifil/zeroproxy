#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/ResumeData_CClosure.hpp"
#include "engine/t7s/hks/ResumeData_Closure.hpp"
#include "engine/t7s/hks/ResumeData_State.hpp"
#include "engine/t7s/hks/ResumeData_Table.hpp"
#include "engine/t7s/hks/ResumeData_UserData.hpp"

namespace t7s::hks {
	union ResumeData_Entry {
		ResumeData_State state_;
		ResumeData_Table hash_table_;
		ResumeData_Closure closure_;
		ResumeData_CClosure c_closure_;
		ResumeData_UserData user_data_;
	};
	ENGINE_ASSERT_SZ(ResumeData_Entry, 0x0020);
}
