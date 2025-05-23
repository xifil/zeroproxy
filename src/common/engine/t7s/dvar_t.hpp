#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/enums/dvarType_t.hpp"

namespace t7s {
	class dvar_t {
	public:
		std::uint32_t name_;		// 0x0000
	private:
		char pad_0004[0x0004];		// 0x0004
	public:
		const char* debug_name_;	// 0x0008
		const char* description_;	// 0x0010
		std::uint32_t flags_;		// 0x0018
		dvarType_t type_;			// 0x001C
		bool modified_;				// 0x0020
	private:
		char pad_0021[0x0007];		// 0x0021
		char pad_0028[0x0070];		// 0x0028
	public:
		dvar_t* hash_next_;			// 0x0098
	};
	ENGINE_ASSERT_SZ(dvar_t, 0x00A0);
}
