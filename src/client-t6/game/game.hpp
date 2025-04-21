#pragma once
#include "common.hpp"
#include "game/function_types.hpp"

namespace game {
	void init();

	bool is_server();

	// Functions
	inline functions::Com_GetBuildVersionT* Com_GetBuildVersion{};

	// Fields
	inline int* unk_GamePatchVersion{};
	inline int* unk_GameVersion{};
}
