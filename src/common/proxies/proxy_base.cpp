#include "common_core.hpp"
#include "proxies/proxy_base.hpp"

#include "loader/component_loader.hpp"
#include "logger/logger.hpp"

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

void proxy::on_dll_process_attach(HMODULE h_mod, bool server) {
	PROTECT_VOID(called);

	if (handle_process_runner()) {
		exit(0);
	}

	DisableThreadLibraryCalls(h_mod);
	logger::console::init();
	logger::console::set_full_title();

	if (!component_loader::should_load()) {
		exit(0);
	}

	if (!component_loader::activate(server)) {
		LOG("EntryPoint", ERROR, "Couldn't activate component loader.");
		return;
	}
	
	if (!component_loader::post_load()) {
		LOG("EntryPoint", ERROR, "Couldn't execute post-load phase of component loader.");
		return;
	}

	LOG("EntryPoint", INFO, "Successfully injected!");
}
