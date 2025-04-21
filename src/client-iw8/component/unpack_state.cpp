#include "common.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

namespace exception_filter {
	namespace {
		HANDLE create_file_a_stub(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
			component_loader::post_unpack();
			return CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
		}
	}

	struct component final : generic_component {
		void post_load() override {
			utils::nt::library game{};
			utils::hook::set(game.get_iat_entry("kernel32.dll", "CreateFileA"), create_file_a_stub);
		}
	};
}

REGISTER_COMPONENT(exception_filter::component)