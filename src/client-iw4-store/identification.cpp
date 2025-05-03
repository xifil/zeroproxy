#include "common.hpp"

extern "C" const char* ext_get_client_name() {
	return "iw4-mod";
}

extern "C" const char* ext_get_target_game() {
	return "Modern Warfare 2";
}

extern "C" void migrate_if_needed() {
	// TODO: move and implement elsewhere
}