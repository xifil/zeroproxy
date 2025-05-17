#include "common.hpp"
#include "game/game.hpp"

#include <memory/signature_store.hpp>
#include <utils/flags.hpp>

#define SETUP_POINTER(name) #name, (void**)&##name
#define SETUP_MOD(mod) [](memory::scanned_result<void> r) { return r.##mod##; }

void game::init() {
	memory::signature_store batch;

	batch.add(SETUP_POINTER(Com_PrintMessage), "40 53 41 54 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24");

	batch.add(SETUP_POINTER(unk_AC_OnDllLoaded), "83 F9 ? 0F 85 ? ? ? ? 48 81 EC");
	
	batch.add(SETUP_POINTER(unk_AC_Unk2_Threaded), "4C 8D 05 ? ? ? ? 33 D2 33 C9 41 FF D2", SETUP_MOD(add(3).rip()));

	batch.add(SETUP_POINTER(unk_AC_Unk3), "48 8D 0D ? ? ? ? 41 FF D0", SETUP_MOD(add(3).rip()));

	batch.add(SETUP_POINTER(unk_AC_Unk4), "48 8D 15 ? ? ? ? 45 33 C0 41 FF D1 FF 05", SETUP_MOD(add(3).rip()));

	batch.add(SETUP_POINTER(unk_AC_Unk5), "48 8D 15 ? ? ? ? 45 33 C0 41 FF D1 4C 8B 05", SETUP_MOD(add(3).rip()));

	batch.add(SETUP_POINTER(unk_AC_Unk6), "E8 ? ? ? ? BB ? ? ? ? 41 FF C5", SETUP_MOD(add(1).rip()));
	
	batch.add(SETUP_POINTER(unk_AC_Unk7), "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B"
		" E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? B8 ? ? ? ? B9 ? ? ? ? 41 BD");
	
	batch.add(SETUP_POINTER(unk_AC_Unk8), "4C 8D 05 ? ? ? ? BA ? ? ? ? 33 C9 41 FF D2 49 89 45 ? FF 15 ? ? ? ? 48 63 C8 4C 69 C1 ? ? ? ? 49 BE",
		SETUP_MOD(add(3).rip()));
	
	batch.add(SETUP_POINTER(unk_AC_Unk10), "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B"
		" E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? B8 ? ? ? ? B9 ? ? ? ? 0F B7 55");
	
	batch.add(SETUP_POINTER(unk_AC_Unk11), "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B"
		" E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? B8 ? ? ? ? B9 ? ? ? ? 44 0F B7 75");

	batch.add(SETUP_POINTER(unk_AC_Unk13_Threaded), "4C 8D 05 ? ? ? ? BA ? ? ? ? 33 C9 41 FF D2 48 89 05", SETUP_MOD(add(3).rip()));

	batch.add(SETUP_POINTER(unk_AC_State), "48 85 05", SETUP_MOD(add(3).rip()));

	batch.scan_all(true);
}

bool game::is_server() {
	static bool is_server = utils::flags::has_flag("dedicated");
	return is_server;
}
