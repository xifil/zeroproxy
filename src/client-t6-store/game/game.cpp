#include "common.hpp"
#include "game/game.hpp"

#include <memory/signature_store.hpp>
#include <utils/flags.hpp>

#define SETUP_POINTER(name) #name, (void**)&##name
#define SETUP_MOD(mod) [](memory::scanned_result<void> r) { return r.##mod##; }

void game::init() {
	memory::signature_store batch;

	if (identification::game::is(t6_store_version::v2_0_0_43_MP, t6_store_version::v2_0_0_43_ZM)) {
		batch.add(SETUP_POINTER(CL_DrawScreen), "40 57 48 81 EC ? ? ? ? 44 8B 0D");
	}
	else if (identification::game::is(t6_store_version::v2_0_0_43_SP)) {
		batch.add(SETUP_POINTER(CL_DrawScreen), "48 8B C4 55 48 81 EC ? ? ? ? 48 8B 15");
	}

	batch.add(SETUP_POINTER(R_AddCmdDrawTextWithCursorInternal), "E8 ? ? ? ? 41 0F 5A DA", SETUP_MOD(add(1).rip()));

	if (identification::game::is(t6_store_version::v2_0_0_43_SP)) {
		batch.add(SETUP_POINTER(sp::sharedUiInfo_assets), "48 8D 05 ? ? ? ? 49 3B D6", SETUP_MOD(add(3).rip()));
	}
	else {
		batch.add(SETUP_POINTER(sharedUiInfo_assets), "48 8D 05 ? ? ? ? 49 3B D6", SETUP_MOD(add(3).rip()));
	}

	batch.scan_all(true);
}

bool game::is_server() {
	static bool is_server = utils::flags::has_flag("dedicated");
	return is_server;
}
