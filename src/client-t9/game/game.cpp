#include "common.hpp"
#include "game/game.hpp"

#include <memory/signature_store.hpp>
#include <utils/flags.hpp>

#define SETUP_POINTER(name) #name, (void**)&##name
#define SETUP_MOD(mod) [](memory::scanned_result<void> r) { return r.##mod##; }

void game::init() {
	memory::signature_store batch;

	batch.add(SETUP_POINTER(BB_Alert), "40 55 53 56 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 80 3D");

	batch.add(SETUP_POINTER(CL_Disconnect), "40 53 56 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 4D 8B F8");

	batch.add(SETUP_POINTER(CL_DrawTextPhysical), "48 83 EC 78 F3 0F 10 84 24 ? ? ? ? F3 0F 10 8C 24 ? ? ? ? 8B 84 24 ? ? ? ? F3 0F 11 44 24 ? F3 0F 10"
		" 84 24 ? ? ? ? C6 44 24 ? ? C7 44 24 ? ? ? ? ? 89 44 24 48 48 8B 84 24 ? ? ? ? 48 89 44 24 ? F3 0F 11 44 24 ? F3 0F 10 84 24 ? ? ? ? F3 0F 11"
		" 4C 24 ? F3 0F 10 8C 24 ? ? ? ? F3 0F 11 44 24 ? F3 0F 11 4C 24 ? E8 ? ? ? ? 48 83 C4 78 C3");

	batch.add(SETUP_POINTER(Com_GametypeSettings_SetGametype), "E9 ? ? ? ? 48 8D 0D ? ? ? ? 45 33 C0 B2 01 48 83 C4 28 E9 ? ? ? ?", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(Com_SessionMode_SetNetworkMode), "8B 05 ? ? ? ? 8B D0 33 D1 83 E2 0F 33 C2 89 05 ? ? ? ? C3");

	batch.add(SETUP_POINTER(Dvar_FindVar), "48 89 5C 24 ? 48 89 4C 24 ? 57 48 83 EC ? 33 DB");

	batch.add(SETUP_POINTER(Dvar_Reset), "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? F7 41 ? ? ? ? ? 8B FA");

	batch.add(SETUP_POINTER(Dvar_SetBoolFromSource), "48 85 C9 0F 84 ? ? ? ? 4C 8B DC 56 57 48 83 EC ? 0F 57 C0 44 0F B6 CA 48 B8 ? ? ? ? ? ? ? ? 41 8B"
		" F0 48 8B F9 0F 11 44 24 ? 0F 11 44 24 ? 48 85 01 0F 84 ? ? ? ?");

	batch.add(SETUP_POINTER(Dvar_SetIntFromSource), "48 85 C9 0F 84 ? ? ? ? 4C 8B DC 56 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ?"
		" ? 0F 57 C0 48 B8 ? ? ? ? ? ? ? ? 41 8B F0 48 8B F9 0F 11 44 24 ? 0F 11 44 24 ? 48 85 01 0F 84 ? ? ? ? 8B 41 ? 49 89 5B ? FF C8 49 89 6B ? 4D"
		" 89 73 ? 83 F8 ? 0F 87 ? ? ? ? 4C 8D 05 ? ? ? ? 48 98 41 8B 8C 80 ? ? ? ? 49 03 C8 FF E1 85 D2");

	batch.add(SETUP_POINTER(LiveUser_GetUserDataForController), "E8 ? ? ? ? 48 8B E8 33 C0 48 89 85 ? ? ? ? 48 8D 4D 10 48 89 85 ? ? ? ? 48 89 85 ? ? ?"
		" ? 89 85 ? ? ? ?", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(LobbyBase_SetNetworkMode), "40 53 48 83 EC 20 8B D9 89 0D ? ? ? ? E8 ? ? ? ? 8B CB E8 ? ? ? ?");

	batch.add(SETUP_POINTER(LobbyData_SetMap), "E8 ? ? ? ? 8B CB E8 ? ? ? ? 84 C0 74 13 8B CB E8 ? ? ? ? 8B C8 BA ? ? ? ?", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(LobbySession_GetControllingLobbySession), "E8 ? ? ? ? 48 8B D7 8B C8 E8 ? ? ? ? 48 8B 7C 24 ? E8 ? ? ? ? 8B CB E8 ? ? ? ?",
		SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(unk_SetScreen), "48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33"
		" C4 48 89 45 27 0F B6 FA 48 63 D9 8B 05 ? ? ? ?");

	batch.add(SETUP_POINTER(unk_SetUsername), "48 89 5C 24 ? 57 48 83 EC 20 48 8B D9 4C 8B C2 BA ? ? ? ? 48 81 C1 ? ? ? ?");

	batch.add(SETUP_POINTER(Dvar_ShowOverStack), "48 8B 0D ? ? ? ? 41 0F 28 F2 F3 0F 5E F0 C7 44 24 ? ? ? ? ? 0F 28 05 ? ? ? ? 0F 28 FE 44 0F 28 C6 F3"
		" 0F 59 3D ? ? ? ? 44 0F 28 CE F3 0F 59 35 ? ? ? ?", SETUP_MOD(add(3).rip()));

	batch.add(SETUP_POINTER(Scr_Initialized), "38 ? ? ? ? ? 0F 85 ? ? ? ? 48 ? 4F B6 E2 AE 25 2E C1 17", SETUP_MOD(add(2).rip()));

	batch.add(SETUP_POINTER(unk_ContentManager), "4C 8B 35 ? ? ? ? 4C 89 BC 24 ? ? ? ? 49 BF", SETUP_MOD(add(3).rip()));

	batch.add(SETUP_POINTER(unk_Config_1), "80 3D ? ? ? ? ? 48 8D 15 ? ? ? ? 48 8B 3F 48 8B C8 48 0F 45 3D ? ? ? ? E8 ? ? ? ?",
		SETUP_MOD(add(2).rip().add(1)));

	batch.add(SETUP_POINTER(unk_Config_2), "80 3D ? ? ? ? ? 75 58 33 C9 48 89 5C 24 ?", SETUP_MOD(add(2).rip().add(1)));

	batch.add(SETUP_POINTER(unk_WatermarkFont), "48 89 05 ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? 48 89 05 ? ? ? ? E8 ? ? ? ? 48 89 05 ? ? ? ? 48 89 1D",
		SETUP_MOD(add(3).rip()));

	batch.add(SETUP_POINTER(exception::Dvar_GetBool), "83 79 ? 01 8B 41 ? 48 89 5C 24 ?");

	batch.scan_all();
}

bool game::is_server() {
	static bool is_server = utils::flags::has_flag("dedicated");
	return is_server;
}

void game::set_mode(int mode, int menu) {
	unk_SetScreen(menu, 0);
	LobbyBase_SetNetworkMode(t9::LobbyNetworkMode::LOBBY_NETWORKMODE_LAN);
	Com_SessionMode_SetNetworkMode(mode);

	*unk_Config_1 = 1;
	*unk_Config_2 = 1;
}
