#include "common.hpp"
#include "component/scheduler.hpp"
#include "game/dvars.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

namespace content_manager {
	namespace {
		void patch_content_manager() {
			if (game::unk_ContentManager && *game::unk_ContentManager) {
				t9::content_manager* mgr = *game::unk_ContentManager;
				for (int i = 0; i < mgr->pack_count_; i++) {
					if (mgr->content_packs_ == nullptr) {
						continue;
					}

					mgr->content_packs_[i].var1_ = 0;
					mgr->content_packs_[i].var2_ = 2;
					mgr->content_packs_[i].var3_ = 3;
				}
			}
			else {
				LOG("Component/ContentManager", ERROR, "Failed to patch content manager.");
			}

			if (GetAsyncKeyState('L') & 0x8000) {
				dvars::set_dvar_bool(dvars::get_dvar_by_name("lobby_forceLAN"), true);
			}
		}
	}

	struct component final : generic_component {
		void post_unpack() override {
			scheduler::loop(patch_content_manager, scheduler::pipeline::renderer);
		}
	};
}

REGISTER_COMPONENT(content_manager::component)