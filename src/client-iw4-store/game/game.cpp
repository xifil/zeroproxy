#include "common.hpp"
#include "game/game.hpp"

#include <memory/signature_store.hpp>
#include <utils/flags.hpp>

#define SETUP_POINTER(name) #name, (void**)&##name
#define SETUP_MOD(mod) [](memory::scanned_result<void> r) { return r.##mod##; }

void game::init() {
	memory::signature_store batch;

	batch.add(SETUP_POINTER(bdLogMessage), "4C 8B DC 55 41 54 41 55");

	batch.add(SETUP_POINTER(CL_DrawTextPhysical), "E8 ? ? ? ? 0F 28 7C 24 ? 4C 8D 5C 24", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(Cmd_AddCommandInternal), "E8 ? ? ? ? 4C 8D 05 ? ? ? ? 48 8D 15 ? ? ? ? 48 8D 0D ? ? ? ? 48 8B 5C 24", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(Com_Frame_Try_Block_Function), "E8 ? ? ? ? FF 05 ? ? ? ? 83 3D", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(G_Glass_Update), "40 53 48 83 EC ? 4C 8B 0D ? ? ? ? 33 DB");

	if (identification::game::is(iw4_store_version::v2_0_6_MP)) {
		batch.add(SETUP_POINTER(ScrPlace_EndFrame), "E8 ? ? ? ? E8 ? ? ? ? B9 ? ? ? ? E8 ? ? ? ? C6 05", SETUP_MOD(add(1).rip()));
	}

	batch.add(SETUP_POINTER(SEH_StringEd_GetString), "48 83 EC ? 48 8B 05 ? ? ? ? 48 85 C0 74 ? 80 78");

	if (identification::game::is(iw4_store_version::v2_0_6_SP)) {
		batch.add(SETUP_POINTER(UI_RefreshFullscreen), "E8 ? ? ? ? 83 3D ? ? ? ? ? 48 8B 7C 24", SETUP_MOD(add(1).rip()));
	}

	batch.add(SETUP_POINTER(sharedUiInfo_assets), "48 8B 05 ? ? ? ? 0F B6 56 ? 48 89 44 24", SETUP_MOD(add(3).rip()));

	batch.scan_all(true);
}

bool game::is_server() {
	static bool is_server = utils::flags::has_flag("dedicated");
	return is_server;
}

bool game::should_enable_demonware_emulator() {
	static bool should_enable_demonware_emulator = utils::flags::has_flag("dw");
	return should_enable_demonware_emulator;
}
