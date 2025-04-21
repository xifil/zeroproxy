#pragma once
#include "scylla/scylla_common.hpp"

namespace scylla {
	class pe_file_section {
	public:
		pe_file_section() {
			ZeroMemory(&this->section_header_, sizeof(IMAGE_SECTION_HEADER));
			this->data_ = nullptr;
			this->data_size_ = 0;
			this->normal_size_ = 0;
		}

		IMAGE_SECTION_HEADER section_header_;
		std::uint8_t* data_;
		std::uint32_t data_size_;
		std::uint32_t normal_size_;
	};
}
