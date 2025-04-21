#include "common.hpp"
#include "game/game.hpp"

#include <memory/signature_store.hpp>
#include <utils/flags.hpp>

#define SETUP_POINTER(name) #name, (void**)&##name
#define SETUP_MOD(mod) [](memory::scanned_result<void> r) { return r.##mod##; }

void game::init() {
	memory::signature_store batch;

	batch.add(SETUP_POINTER(Com_GameInfo_GetGameTypeForInternalName), "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 8B 35 ? ? ? ? 45 33 DB 48 8B E9");

	batch.add(SETUP_POINTER(Com_GameInfo_GetMapInfoForLoadName), "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 8B 3D ? ? ? ? 45 33 DB 48 8B E9");

	batch.add(SETUP_POINTER(Dvar_GetIntSafe), "E8 ? ? ? ? 8B D0 85 C0 75 ? 38 05", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(Dvar_GetStringSafe), "48 83 EC ? E8 ? ? ? ? 8B C8 E8 ? ? ? ? 48 85 C0 75 ? 48 8D 05 ? ? ? ? 48 83 C4 ? C3 80 78");

	if (identification::game::is(identification::game::version::iw8::v1_20_4_7623265_REPLAY, identification::game::version::iw8::v1_20_4_7623265_SHIP)) {
		batch.add(SETUP_POINTER(R_EndFrame), "48 8B 15 ? ? ? ? 45 33 D2 4C 8B 0D");
	}
	else if (identification::game::is(identification::game::version::iw8::v1_38_3_9489393, identification::game::version::iw8::v1_44_0_10435696)) {
		batch.add(SETUP_POINTER(R_EndFrame), "48 83 EC ? E8 ? ? ? ? 48 8B 15 ? ? ? ? 45 33 D2");
	}

	if (identification::game::is(identification::game::version::iw8::v1_20_4_7623265_REPLAY, identification::game::version::iw8::v1_20_4_7623265_SHIP)) {
		batch.add(SETUP_POINTER(SEH_StringEd_GetString), "E8 ? ? ? ? 48 8B CB 48 8B F8 E8 ? ? ? ? 48 8B D0 48 8B CF E8 ? ? ? ? 4C 8B 05 ? ? ? ? 48 8D"
			" 0D ? ? ? ? 48 8B D0 E8 ? ? ? ? 48 8B 0D", SETUP_MOD(add(1).rip()));
	}
	else if (identification::game::is(identification::game::version::iw8::v1_38_3_9489393, identification::game::version::iw8::v1_44_0_10435696)) {
		batch.add(SETUP_POINTER(SEH_StringEd_GetString), "E8 ? ? ? ? 48 8B D0 80 FB", SETUP_MOD(add(1).rip()));
	}
	
	batch.add(SETUP_POINTER(s_luaInFrontend), "0F B6 05 ? ? ? ? 75", SETUP_MOD(add(3).rip()));

	batch.scan_all();
}

bool game::is_server() {
	static bool is_server = utils::flags::has_flag("dedicated");
	return is_server;
}
