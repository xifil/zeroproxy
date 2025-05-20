#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/enums/ObjectType.hpp"

namespace t7s::hks {
	class ResumeData_Header {
	public:
		ObjectType type_;	// 0x0000
	};
	ENGINE_ASSERT_SZ(ResumeData_Header, 0x0004);
}
