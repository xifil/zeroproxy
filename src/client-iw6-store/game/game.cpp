#include "common.hpp"
#include "game/game.hpp"

#include <memory/signature_store.hpp>
#include <utils/flags.hpp>

#define SETUP_POINTER(name) #name, (void**)&##name
#define SETUP_MOD(mod) [](memory::scanned_result<void> r) { return r.##mod##; }

void game::init() {
	memory::signature_store batch;

	batch.add(SETUP_POINTER(Com_Frame_Try_Block_Function), "E8 ? ? ? ? FF 05 ? ? ? ? 83 3D", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(LUI_OpenMenu), "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 41 8B E9 45 8B F0");

	batch.add(SETUP_POINTER(R_AddCmdDrawText), "E8 ? ? ? ? 48 8B 75 ? 49 C7 C6", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(R_EndFrame), "40 53 48 83 EC ? 48 8B 15 ? ? ? ? 48 8B 05");

	batch.add(SETUP_POINTER(SEH_StringEd_GetString), "48 83 EC ? 48 8B 05 ? ? ? ? 48 85 C0 74 ? 80 78 ? ? 74");

	if (identification::game::is(identification::game::version::iw6_store::v3_15_11_MP)) {
		batch.add(SETUP_POINTER(sharedUiInfo_assets), "4C 8D 3D ? ? ? ? 48 63 CF", SETUP_MOD(add(3).rip()));
	}
	else if (identification::game::is(identification::game::version::iw6_store::v3_15_11_SP)) {
		batch.add(SETUP_POINTER(sharedUiInfo_assets), "48 89 05 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? BA ? ? ? ? 48 89 05 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? BA"
			" ? ? ? ? 48 89 05 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? BA ? ? ? ? 48 89 05 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? BA ? ? ? ? 48 89 05 ? ? ? ? 48 8D 0D"
			" ? ? ? ? E8 ? ? ? ? BA ? ? ? ? 48 89 05 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? BA ? ? ? ? 48 89 05 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 33 D2",
			SETUP_MOD(add(3).rip()));
	}

	batch.scan_all();
}

bool game::is_server() {
	static bool is_server = utils::flags::has_flag("dedicated");
	return is_server;
}
