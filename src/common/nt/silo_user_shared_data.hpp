#pragma once
#include "common_core.hpp"
#include "nt/system_time.hpp"
#include "nt/enums/nt_product_type.hpp"

namespace nt {
	class silo_user_shared_data {
	public:
		unsigned long service_session_id_;					// 0x0000
		unsigned long active_console_id_;					// 0x0004
		long long console_session_foreground_process_id_;	// 0x0008
		nt_product_type nt_product_type_;					// 0x0010
		unsigned long suite_mask_;							// 0x0014
		unsigned long shared_user_session_id_;				// 0x0018 - since RS2
		bool is_multi_session_sku_;							// 0x001C
		wchar_t nt_system_root_[260];						// 0x001E
		std::uint16_t user_mode_global_logger_[16];			// 0x0226
		unsigned long time_zone_id_;						// 0x0248 - since 21H2
		long time_zone_bias_stamp_;							// 0x024C
		system_time time_zone_bias_;						// 0x0250
	private:
		char pad_025C[0x0004];								// 0x025C
	public:
		LARGE_INTEGER time_zone_bias_effective_start_;		// 0x0260
		LARGE_INTEGER time_zone_bias_effective_end_;		// 0x0268
	};
	CLASS_ASSERT_SZ_64(silo_user_shared_data, 0x0270);
}
