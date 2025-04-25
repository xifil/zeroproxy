#include "common.hpp"

extern "C" const char* ext_get_client_name() {
	return "t9-mod";
}

extern "C" const char* ext_get_target_game() {
	return "Black Ops Cold War";
}

extern "C" void migrate_if_needed() {
	// TODO: move and implement elsewhere
}