#include "common.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

namespace unpack_state {
	namespace {
		utils::hook::iat_detour set_thread_affinity_mask_hook;

		DWORD_PTR set_thread_affinity_mask_stub(HANDLE hThread, DWORD_PTR dwThreadAffinityMask) {
			component_loader::post_unpack();
			return set_thread_affinity_mask_hook.invoke<DWORD_PTR>(hThread, dwThreadAffinityMask);
		}
	}

	struct component final : generic_component {
		void post_load() override {
			//set_thread_affinity_mask_hook.create({}, "kernel32.dll", "SetThreadAffinityMask", set_thread_affinity_mask_stub);
		}
	};
}

REGISTER_COMPONENT(unpack_state::component)