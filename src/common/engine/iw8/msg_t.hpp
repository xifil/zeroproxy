#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/enums/netsrc_t.hpp"

namespace iw8 {
	class msg_t {
	public:
		int overflowed_;					// 0x0000
		int read_only_;						// 0x0004
		std::uint8_t* data_;				// 0x0008
		std::uint8_t* split_data_;			// 0x0010
		int max_size_;						// 0x0018
		int cur_size_;						// 0x001C
		int split_size_;					// 0x0020
		int read_count_;					// 0x0024
		int bit_;							// 0x0028
		int last_entity_ref_;				// 0x002C
		netsrc_t target_local_net_id_;		// 0x0030
		std::uint32_t compression_flags_;	// 0x0034
	};
	ENGINE_ASSERT_SZ(msg_t, 0x0038);
}
