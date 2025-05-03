#pragma once
#include "common_core.hpp"
#include "nt/assembly_storage_map_entry.hpp"

namespace nt {
	class assembly_storage_map {
	public:
		unsigned long flags_;							// 0x0000
		unsigned long assembly_count_;					// 0x0004
		assembly_storage_map_entry** assembly_array_;	// 0x0008
	};
	CLASS_ASSERT_SZ_64(assembly_storage_map, 0x0010);
}
