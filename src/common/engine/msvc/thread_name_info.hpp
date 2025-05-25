#pragma once
#include "engine/engine_common.hpp"

namespace msvc {
	class thread_name_info {
	public:
		std::uint32_t type_;		// 0x0000
	private:
		char pad_0004[0x0004];		// 0x0004
	public:
		const char* name_;			// 0x0008
		std::uint32_t thread_id_;	// 0x0010
		std::uint32_t flags_;		// 0x0014
	};
	ENGINE_ASSERT_SZ(thread_name_info, 0x0018);
}
