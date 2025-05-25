#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	class MaterialSerializedShader {
	public:
		const char* name_;				// 0x0000
		const char* debug_name_;		// 0x0008
		std::uint8_t* program_;			// 0x0010
		std::uint8_t* meta_data_;		// 0x0018
		std::uint32_t program_size_;	// 0x0020
		std::uint32_t meta_data_size_;	// 0x0024
		std::uint32_t micro_code_crc_;	// 0x0028
	private:
		char pad_002C[0x0004];			// 0x002C
	};
	ENGINE_ASSERT_SZ(MaterialSerializedShader, 0x0030);
}
