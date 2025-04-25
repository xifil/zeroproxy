#include "common.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

namespace unpack_state {
	namespace {
		utils::hook::iat_detour create_file_a_hook;

		HANDLE create_file_a_stub(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
			component_loader::post_unpack();
			return create_file_a_hook.invoke<HANDLE>(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
		}
	}

	struct component final : generic_component {
		void post_load() override {
			create_file_a_hook.create({}, "kernel32.dll", "CreateFileA", create_file_a_stub);
		}
	};
}

REGISTER_COMPONENT(unpack_state::component)