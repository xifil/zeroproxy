#pragma once
#include "engine/engine_common.hpp"

namespace t7s {
	class ClientGameState {
	public:
		int flags_;				// 0x0000
		int local_client_num_;	// 0x0004
		int controller_index_;	// 0x0008
	private:
		char pad_000C[0x0018];	// 0x000C
	};
	ENGINE_ASSERT_SZ(ClientGameState, 0x0024);
}
