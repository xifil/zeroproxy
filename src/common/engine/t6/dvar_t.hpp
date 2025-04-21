#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/DvarLimits.hpp"
#include "engine/t6/DvarValue.hpp"
#include "engine/t6/enums/dvarType_t.hpp"

namespace t6 {
	class alignas(8) dvar_t {
	public:
		const char* name_;			// 0x0000
		const char* description_;	// 0x0004
		int hash_;					// 0x0008
		std::uint32_t flags_;		// 0x000C
		dvarType_t type_;			// 0x0010
		bool modified_;				// 0x0014
	private:
		char pad_0015[0x0003];		// 0x0015
	public:
		DvarValue current_;			// 0x0018
		DvarValue latched_;			// 0x0028
		DvarValue reset_;			// 0x0038
		DvarLimits domain_;			// 0x0048
		dvar_t* hash_next_;			// 0x0058
	};
	ENGINE_ASSERT_SZ(dvar_t, 0x0060);
}
