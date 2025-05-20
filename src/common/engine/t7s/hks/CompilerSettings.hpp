#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/enums/BytecodeSharingFormat.hpp"
#include "engine/t7s/hks/enums/IntLiteralOptions.hpp"

namespace t7s::hks {
	inline int identity_map(const char* file_name, int lua_line) {
		return lua_line;
	}

	class CompilerSettings {
	public:
		int emit_struct_code_ = 0;																	// 0x0000
	private:
		char pad_0004[0x0004];																		// 0x0004
	public:
		const char** strip_names_ = 0;																// 0x0008
		BytecodeSharingFormat bytecode_sharing_format_ = BytecodeSharingFormat::BYTECODE_INPLACE;	// 0x0010
		IntLiteralOptions enable_int_literals_ = IntLiteralOptions::INT_LITERALS_NONE;				// 0x0014
		DebugMapT debug_map_ = identity_map;														// 0x0018
	};
	ENGINE_ASSERT_SZ(CompilerSettings, 0x0020);
}
