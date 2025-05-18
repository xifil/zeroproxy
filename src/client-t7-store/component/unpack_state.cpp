#include "common.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

namespace unpack_state {
	namespace {
		utils::hook::detour unk_init_sys_dvars_hook;

		void unk_init_sys_dvars_stub() {
			unk_init_sys_dvars_hook.invoke<void>();
			component_loader::post_unpack();
		}
	}

	struct component final : generic_component {
		void post_load() override {
			unk_init_sys_dvars_hook.create(game::unk_InitSysDvars, unk_init_sys_dvars_stub);
		}
	};
}

REGISTER_COMPONENT(unpack_state::component)
