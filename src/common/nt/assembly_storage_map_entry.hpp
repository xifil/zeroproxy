#pragma once
#include "common_core.hpp"

namespace nt {
	class assembly_storage_map_entry {
	public:
		unsigned long flags_;		// 0x0000
	private:
		char pad_0004[0x0004];		// 0x0004
	public:
		UNICODE_STRING dos_path_;	// 0x0008
		HANDLE handle_;				// 0x0018
	};
	CLASS_ASSERT_SZ_64(assembly_storage_map_entry, 0x0020);
}
