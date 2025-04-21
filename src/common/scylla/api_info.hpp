#pragma once
#include "scylla/scylla_common.hpp"

namespace scylla {
	class module_info;

	class api_info {
	public:
		char name_[MAX_PATH];
		std::uint16_t hint_;
		std::uintptr_t va_;
		std::uintptr_t rva_;
		std::uint16_t ordinal_;
		bool is_forwarded_;
		module_info* module_;
	};
}
