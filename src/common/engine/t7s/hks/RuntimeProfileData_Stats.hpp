#pragma once
#include "engine/engine_common.hpp"

namespace t7s::hks {
	class RuntimeProfileData_Stats {
	public:
		std::uint64_t hks_time_;				// 0x0000
		std::uint64_t callback_time_;			// 0x0008
		std::uint64_t gc_time_;					// 0x0010
		std::uint64_t c_finalizer_time_;		// 0x0018
		std::uint64_t compiler_time_;			// 0x0020
		std::uint32_t hkss_time_samples_;		// 0x0028
		std::uint32_t callback_time_samples_;	// 0x002C
		std::uint32_t gc_time_samples_;			// 0x0030
		std::uint32_t compiler_time_samples_;	// 0x0034
		std::uint32_t num_new_user_data_;		// 0x0038
		std::uint32_t num_table_rehash_;		// 0x003C
		std::uint32_t num_push_string_;			// 0x0040
		std::uint32_t num_push_cfunction_;		// 0x0044
		std::uint32_t num_new_tables_;			// 0x0048
	private:
		char pad_004C[0x0004];					// 0x004C
	};
	ENGINE_ASSERT_SZ(RuntimeProfileData_Stats, 0x0050);
}
