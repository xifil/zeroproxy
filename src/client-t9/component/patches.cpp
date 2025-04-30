#include "common.hpp"

#include "component/scheduler.hpp"
#include "game/dvars.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

namespace patches {
	namespace {
		void disable_demonware() {
			dvars::set_dvar_bool(dvars::get_dvar_by_name("noDW"), true);
			game::CL_Disconnect(0, false, "");
		}
	}

	struct component final : generic_component {
		void post_unpack() override {
			CreateThread(nullptr, 0, [](PVOID) -> DWORD {
				while (!(*game::Scr_Initialized)) {
					std::this_thread::sleep_for(100ms);
				}

				disable_demonware();
				game::unk_SetUsername(game::LiveUser_GetUserDataForController(0), "the player");
				game::set_mode(0, 10);

				LOG("Component/Patches", DEBUG, "Patched auth.");

				return 0;
			}, nullptr, 0, nullptr);
		}
	};
}

REGISTER_COMPONENT(patches::component)