#include "common.hpp"

extern "C" const char* ext_get_client_name() {
	return "t6s";
}

extern "C" const char* ext_get_target_game() {
	return "Black Ops II";
}

extern "C" void migrate_if_needed() {
	// TODO: move and implement elsewhere
}