#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/SocialPresence.hpp"

namespace iw8 {
	class LocalUserPresenceData {
	public:
		SocialPresence current_;	// 0x0000
		int last_update_timestamp_;	// 0x0030
		int next_update_timestamp_;	// 0x0034
	};
	ENGINE_ASSERT_SZ(LocalUserPresenceData, 0x0038);
}
