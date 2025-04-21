#pragma once
#include "scylla/scylla_common.hpp"

namespace scylla {
	class api_info;

	class module_info {
	public:
		wchar_t full_path_[MAX_PATH] = { 0 };
		std::uintptr_t mod_base_addr_;
		std::uint32_t mod_base_size_;

		bool is_already_parsed_;
		bool parsing_;

		/*
		  for iat rebuilding with duplicate entries:

		  ntdll = low priority
		  kernelbase = low priority
		  SHLWAPI = low priority

		  kernel32 = high priority

		  priority = 1 -> normal/high priority
		  priority = 0 -> low priority
		*/
		int priority_;

		std::vector<api_info*> api_list_;

		module_info() {
			this->mod_base_addr_ = 0;
			this->mod_base_size_ = 0;
			this->priority_ = 1;
			this->is_already_parsed_ = false;
			this->parsing_ = false;
		}

		const WCHAR* get_filename() const {
			const WCHAR* slash = wcsrchr(this->full_path_, L'\\');
			if (slash) {
				return slash + 1;
			}
			return this->full_path_;
		}
	};
}
