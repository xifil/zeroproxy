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
			static std::string watermarkText = std::format("{}: " GIT_DESCRIBE " [v{}]", identification::client::get_client_name(),
				identification::game::get_version().version_);

			t9::Font_s* font = *game::unk_WatermarkFont;
			if (font) {
				float color[4] = { .666f, .666f, .666f, .666f };
				game::CL_DrawTextPhysical(watermarkText.c_str(), 0x7FFFFFFF, font, 4.f, 4.f + static_cast<float>(font->font_height_),
					1.f, 1.f, 0.f, color, 0, 0);
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