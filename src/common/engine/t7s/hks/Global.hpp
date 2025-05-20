#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/CompilerSettings.hpp"
#include "engine/t7s/hks/DebugInstance.hpp"
#include "engine/t7s/hks/GarbageCollector.hpp"
#include "engine/t7s/hks/MemoryManager.hpp"
#include "engine/t7s/hks/RuntimeProfileData.hpp"
#include "engine/t7s/hks/StaticStringCache.hpp"
#include "engine/t7s/hks/StringTable.hpp"
#include "engine/t7s/hks/enums/BytecodeEndianness.hpp"
#include "engine/t7s/hks/enums/BytecodeSharingMode.hpp"

namespace t7s::hks {
	class Global {
	public:
		MemoryManager memory_;								// 0x0000
		GarbageCollector collector_;						// 0x0058
		StringTable string_table_;							// 0x01B8
	private:
		char pad_01D0[0x0008];								// 0x01D0
	public:
		BytecodeSharingMode bytecode_sharing_mode_;			// 0x01D8
	private:
		char pad_01E0[0x0008];								// 0x01E0
	public:
		Object registry_;									// 0x01E8
		ChunkList user_data_list_;							// 0x01F8
		lua_State* root_;									// 0x0208
		StaticStringCache static_string_cache_;				// 0x0210
		DebugInstance* debugger_;							// 0x04B0
		void* profiler_;									// 0x04B8
		RuntimeProfileData run_profiler_data_;				// 0x04C0
		CompilerSettings compiler_settings_;				// 0x0570
		lua_CFunction panic_function_;						// 0x0590
		void* lua_plus_object_list_;						// 0x0598
		int heap_assertion_frequency_;						// 0x05A0
		int heap_assertion_count_;							// 0x05A4
		LogFuncT log_function_;								// 0x05A8
		EmergencyGCFailFuncT emergency_gc_fail_function_;	// 0x05B0
		BytecodeEndianness bytecode_dump_endianness_;		// 0x05B8
	private:
		char pad_05B4[0x0004];								// 0x05BC
	};
	ENGINE_ASSERT_SZ(Global, 0x05C0);
}
