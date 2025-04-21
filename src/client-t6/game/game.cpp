#include "common.hpp"
#include "game/game.hpp"

#include <memory/signature_store.hpp>
#include <utils/flags.hpp>

#define SETUP_POINTER(name) #name, (void**)&##name
#define SETUP_MOD(mod) [](memory::scanned_result<void> r) { return r.##mod##; }

void game::init() {
	memory::signature_store batch;

	batch.add(SETUP_POINTER(Com_GetBuildVersion), "8B 0D ? ? ? ? A1 ? ? ? ? 8B 15 ? ? ? ? 51");

	batch.add(SETUP_POINTER(unk_GamePatchVersion), "8B 0D ? ? ? ? 33 C0 3B 0D", SETUP_MOD(add(2).rel()));

	batch.add(SETUP_POINTER(unk_GameVersion), "A3 ? ? ? ? 85 C0 0F 89", SETUP_MOD(add(1).rel()));

	batch.scan_all();
}

bool game::is_server() {
	static bool is_server = utils::flags::has_flag("dedicated");
	return is_server;
}
