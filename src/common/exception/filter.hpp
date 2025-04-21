#pragma once
#include "common_core.hpp"

namespace exception {
	void ensure_dbg_help();
	long WINAPI filter(EXCEPTION_POINTERS* inf);
}
