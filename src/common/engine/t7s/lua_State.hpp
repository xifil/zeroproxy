#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/ApiStack.hpp"
#include "engine/t7s/hks/CallSite.hpp"
#include "engine/t7s/hks/CallStack.hpp"
#include "engine/t7s/hks/ChunkHeader.hpp"
#include "engine/t7s/hks/DebugHook.hpp"
#include "engine/t7s/hks/Global.hpp"
#include "engine/t7s/hks/Object.hpp"
#include "engine/t7s/hks/enums/Error.hpp"

namespace t7s {
	class lua_State {
	public:
		enum class Status {
			NEW = 1,
			RUNNING = 2,
			YIELDED = 3,
			DEAD_ERROR = 4
		};

		hks::ChunkHeader base_class_;	// 0x0000
		hks::Global* global_;			// 0x0010
		hks::CallStack call_stack_;		// 0x0018
		hks::ApiStack api_stack_;		// 0x0048
		hks::UpValue* pending_;			// 0x0068
		hks::Object globals_;			// 0x0070
		hks::Object c_env_;				// 0x0080
		hks::CallSite* call_sites_;		// 0x0090
		int number_of_c_calls_;			// 0x0098
	private:
		char pad_009C[0x0004];			// 0x009C
	public:
		void* context_;					// 0x00A0
		hks::InternString* name_;		// 0x00A8
		lua_State* next_;				// 0x00B0
		lua_State* next_state_stack_;	// 0x00B8
		Status status_;					// 0x00C0
		hks::Error error_;				// 0x00C4
		hks::DebugHook debug_hook_;		// 0x00C8
	};
	ENGINE_ASSERT_SZ(lua_State, 0x00E8);
}
