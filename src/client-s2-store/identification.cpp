#include "common.hpp"

extern "C" const char* ext_get_client_name() {
	return "s2-mod";
}

extern "C" const char* ext_get_target_game() {
	return "WWII";
}

extern "C" void migrate_if_needed() {
	// TODO: move and implement elsewhere
}