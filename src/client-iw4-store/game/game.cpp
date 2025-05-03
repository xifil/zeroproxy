#include "common.hpp"
#include "game/game.hpp"

#include <memory/signature_store.hpp>
#include <utils/flags.hpp>

#define SETUP_POINTER(name) #name, (void**)&##name
#define SETUP_MOD(mod) [](memory::scanned_result<void> r) { return r.##mod##; }

void game::init() {
	memory::signature_store batch;

	batch.add(SETUP_POINTER(Cmd_AddCommandInternal), "E8 ? ? ? ? 4C 8D 05 ? ? ? ? 48 8D 15 ? ? ? ? 48 8D 0D ? ? ? ? 48 8B 5C 24", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(unk_InitGameRuntime), "E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 33 C9 E8 ? ? ? ? 84 C0", SETUP_MOD(add(1).rip()));

	batch.scan_all(true);
}

bool game::is_server() {
	static bool is_server = utils::flags::has_flag("dedicated");
	return is_server;
}
