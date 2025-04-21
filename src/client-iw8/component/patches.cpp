#include "common.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

namespace patches {
	namespace {
		void mystery_function_stub() {
			// do nothing
		}
	}

	struct component final : generic_component {
		void post_load() override {
			// stop the game from crashing on launch by skipping this one function - still unclear what it actually does.
			switch (identification::game::get_version()) {
			case identification::game::version::iw8::v1_20_4_7623265_REPLAY:
				utils::hook::jump(0x3061A0_b, mystery_function_stub);
				break;
			case identification::game::version::iw8::v1_20_4_7623265_SHIP:
				utils::hook::set(0x3DF4548_b, mystery_function_stub);
				break;
			default:
				LOG("Component/Patches", WARN, "Failed to patch \"mystery function\" - if you're on Windows 11, there is a crash most likely imminent.");
				break;
			}
		}
	};
}

REGISTER_COMPONENT(patches::component)