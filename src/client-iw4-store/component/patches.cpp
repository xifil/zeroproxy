#include "common.hpp"

#include "component/scheduler.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

namespace patches {
	namespace {
		bool unk_init_game_runtime_stub() {
			if (identification::game::is(identification::game::version::iw4_store::v1_0_0_MP)) {
				game::Cmd_AddCommandInternal("target_menu_specialops", PTR_AS(void(*)(), 0x1B5FD0_b), PTR_AS(iw4::cmd_function_s*, 0x1A50700_b));
				game::Cmd_AddCommandInternal("target_menu_campaign", PTR_AS(void(*)(), 0x1B5FB0_b), PTR_AS(iw4::cmd_function_s*, 0x1A50718_b));
				game::Cmd_AddCommandInternal("target_menu_privateparty", PTR_AS(void(*)(), 0x1B5FC0_b), PTR_AS(iw4::cmd_function_s*, 0x1A50730_b));
			}

			if (identification::game::is(identification::game::version::iw4_store::v1_0_0_SP)) {
				game::Cmd_AddCommandInternal("target_menu_specialops", PTR_AS(void(*)(), 0x1BF230_b), PTR_AS(iw4::cmd_function_s*, 0x11F8E00_b));
				game::Cmd_AddCommandInternal("target_menu_campaign", PTR_AS(void(*)(), 0x1BF220_b), PTR_AS(iw4::cmd_function_s*, 0x11F8E28_b));
			}

			return true;
		}
	}

	struct component final : generic_component {
		void post_load() override {
			utils::hook::jump(game::unk_InitGameRuntime, unk_init_game_runtime_stub);
		}
	};
}

REGISTER_COMPONENT(patches::component)