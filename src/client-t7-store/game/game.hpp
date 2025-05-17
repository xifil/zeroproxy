#pragma once
#include "common.hpp"
#include "game/function_types.hpp"

namespace game {
	void init();

	inline functions::Com_PrintMessageT* Com_PrintMessage{};

	bool is_server();
}
