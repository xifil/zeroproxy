#pragma once
#include "engine/engine_common.hpp"
#include "engine/t9/DvarData.hpp"
#include "engine/t9/enums/dvarType_t.hpp"

namespace t9 {
	class dvar_t {
	public:
		std::int64_t name_hash_;	// 0x0000
	private:
		char pad_0008[0x0008];		// 0x0008
	public:
		DvarData* value_;			// 0x0010
		dvarType_t type_;			// 0x0018
		std::uint32_t flags_;		// 0x001C
	private:
		char pad_0020[0x0020];		// 0x0020
	};
	ENGINE_ASSERT_SZ(dvar_t, 0x0040);
}
