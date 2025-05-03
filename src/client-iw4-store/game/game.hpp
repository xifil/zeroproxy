#pragma once
#include "common.hpp"
#include "game/function_types.hpp"

namespace game {
	void init();

	inline functions::Cmd_AddCommandInternalT* Cmd_AddCommandInternal{};
	inline functions::unk_InitGameRuntimeT* unk_InitGameRuntime{};

	bool is_server();
}
