#pragma once
#include "common.hpp"

#include <engine/iw4/cmd_function_s.hpp>

namespace functions {
	using Cmd_AddCommandInternalT = void(const char* cmd_name, void(*function)(), iw4::cmd_function_s* alloced_cmd);
	using unk_InitGameRuntimeT = bool();
}
