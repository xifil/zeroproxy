#pragma once
#include "common.hpp"

#include <utils/hook.hpp>

namespace lua_hook {
	void create(utils::hook::detour& detour, const std::string& name, void* target);
}
