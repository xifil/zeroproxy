#include "common.hpp"
#include "game/game.hpp"

#include <proxies/d3d11.dll.hpp>

BOOL APIENTRY DllMain(HMODULE h_mod, DWORD reason, PVOID) {
	client_module = h_mod;
	if (reason == DLL_PROCESS_ATTACH) {
		proxy::on_dll_process_attach(h_mod, game::is_server());
	}
	return TRUE;
}
