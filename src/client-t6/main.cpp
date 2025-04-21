#include "common.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <proxies/d3d11.dll.hpp>

bool handle_process_runner() {
	const auto* const command = "-proc ";
	const char* parent_proc = strstr(GetCommandLineA(), command);

	if (!parent_proc) {
		return false;
	}

	const auto pid = static_cast<DWORD>(atoi(parent_proc + strlen(command)));
	if (const auto process_handle = OpenProcess(SYNCHRONIZE, FALSE, pid)) {
		WaitForSingleObject(process_handle, INFINITE);
	}

	return true;
}

void on_dll_process_attach(HMODULE hMod) {
	PROTECT_VOID(called);

	if (handle_process_runner()) {
		exit(0);
	}

	utils::nt::library game{};

	DisableThreadLibraryCalls(hMod);
	std::string client_name = identification::client::get_client_name();
	logger::console::init(client_name);

	bool try_load_client = true;
	
	LOG("EntryPoint", INFO, "Trying version check...");
	auto version = identification::game::get_version();
	if (identification::game::is_game("Black Ops II")) {
		SetConsoleTitleA(std::format("{}: [zeroproxy pre-release] - {}", client_name, version.get_full_display_name()).c_str());
	}
	else {
		LOG("EntryPoint", INFO, "Unknown executable '{}' (checksum: 0x{:08X})", game.get_name(), version.checksum_);
		SetConsoleTitleA(std::format("{}: [zeroproxy pre-release] - unknown-{:08X}", client_name, version.checksum_).c_str());

		try_load_client = MessageBoxA(nullptr, "This client has been launched on an unknown game/game version. Try to load anyway?", client_name.c_str(), MB_YESNO) == IDYES;
	}

	if (try_load_client) {
		if (!component_loader::activate(game::is_server())) {
			LOG("EntryPoint", ERROR, "Couldn't activate component loader.");
			return;
		}
	
		if (!component_loader::post_load()) {
			LOG("EntryPoint", ERROR, "Couldn't execute post-load phase of component loader.");
			return;
		}
	}

	LOG("EntryPoint", INFO, "Entry done.");
}

BOOL APIENTRY DllMain(HMODULE hMod, DWORD reason, PVOID) {
	client_module = hMod;
	if (reason == DLL_PROCESS_ATTACH) {
		on_dll_process_attach(hMod);
	}
	return TRUE;
}
