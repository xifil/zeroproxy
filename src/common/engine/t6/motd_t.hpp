#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class motd_t {
	public:
		int version_;							// 0x0000
		bool single_view_;						// 0x0004
	private:
		char pad_0005[0x0003];					// 0x0005
	public:
		int expiration_;						// 0x0008
		std::uint16_t image_category_;			// 0x000C
		char title_[0x40 + 1];					// 0x000E
		char message_[0x400 + 1];				// 0x004F
		char image_[0x20 + 1];					// 0x0450
		char action_[0x20];						// 0x0471
		char action_context_[0x40 + 1];			// 0x0491
		char action_string_[0x40 + 1];			// 0x04D2
		char banner_title_[0x40 + 1];			// 0x0513
		char banner_message_[0x80 + 1];			// 0x0554
		char banner_image_[0x20 + 1];			// 0x05D5
		char banner_action_[0x20];				// 0x05F6
		char banner_action_context_[0x40 + 1];	// 0x0616
		char banner_action_string_[0x40 + 1];	// 0x0657
		char elite_image_[0x20 + 1];			// 0x0698
		char founder_image_[0x20 + 1];			// 0x06B9
		bool is_valid_;							// 0x06DA
	private:
		char pad_06DB[0x0001];					// 0x06DB
	};
	ENGINE_ASSERT_SZ(motd_t, 0x06DC);
}
