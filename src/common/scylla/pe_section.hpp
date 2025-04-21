#pragma once
#include "scylla/scylla_common.hpp"

namespace scylla {
	class pe_section {
	public:
		wchar_t name_[IMAGE_SIZEOF_SHORT_NAME + 1];
		std::uintptr_t virtual_address_;
		std::uint32_t virtual_size_;
		std::uint32_t raw_address_;
		std::uint32_t raw_size_;
		std::uint32_t characteristics_;

		bool is_dumped_;

		bool highlight_virtual_size();
	};
}
