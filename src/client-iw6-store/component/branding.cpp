#include "common.hpp"

#include "component/scheduler.hpp"
#include "game/game.hpp"

#include <identification/client.hpp>
#include <identification/game.hpp>
#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

#include <version.hpp>

namespace branding {
	namespace {
		void draw_branding() {
			static std::string watermark_text = std::format("{}: " GIT_DESCRIBE " [v{}]", identification::client::get_client_name(),
				identification::game::get_version().version_);

			auto font = game::sharedUiInfo_assets->text_font_;
			if (font != nullptr) {
				float scale = .5f;
				float color[4] = { .666f, .666f, .666f, .666f };
				game::R_AddCmdDrawText(watermark_text.c_str(), 0x7FFFFFFF, font, 4.f, 4.f + static_cast<float>(font->pixel_height_) * scale,
					scale, scale, 0.f, color, 0);
			}
		}
	}

	struct component final : generic_component {
		void post_unpack() override {
			scheduler::loop(draw_branding, scheduler::pipeline::renderer);
		}
	};
}

REGISTER_COMPONENT(branding::component)
