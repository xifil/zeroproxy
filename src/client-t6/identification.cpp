#include "common.hpp"
#include <utils/io.hpp>

extern "C" const char* ext_get_client_name() {
	return "t6-mod";
}

extern "C" const char* ext_get_target_game() {
	return "Black Ops II";
}

extern "C" void migrate_if_needed() {
	// TODO: move and implement elsewhere
	std::error_code e;

	// Folder does not exist. Nothing to migrate
	if (!std::filesystem::is_directory("players", e)) {
		return;
	}

	// Folder does exist. Already migrated
	if (std::filesystem::is_directory("t6m_players", e)) {
		return;
	}

	utils::io::create_directory("t6m_players");

	std::filesystem::copy("players", "t6m_players", std::filesystem::copy_options::recursive, e);
}