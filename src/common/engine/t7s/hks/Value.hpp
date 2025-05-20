#pragma once
#include "engine/engine_common.hpp"

namespace t7s::hks {
	union Value {
		CClosure* c_closure_;
		Closure* closure_;
		UserData* user_data_;
		HashTable* table_;
		StructInst* struct_;
		InternString* str_;
		lua_State* thread_;
		void* ptr_;
		float number_;
		std::uint32_t native_;
		int boolean_;
	};
	ENGINE_ASSERT_SZ(Value, 0x0008);
}
