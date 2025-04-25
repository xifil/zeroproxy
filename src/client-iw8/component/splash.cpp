#include "common.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

#include "resource.h"

namespace splash {
	namespace {
		utils::hook::iat_detour load_image_a_hook;

		HANDLE load_image_a_stub(HINSTANCE h_inst, LPCSTR name, UINT type, int c_x, int c_y, UINT fu_load) {
			if (PTR_AS(std::uintptr_t, name) == 0x64) {
				while (!component_loader::is_post_unpack_phase_complete()) {
					Sleep(100);
				}

				int id;
				switch (identification::game::get_version()) {
				case identification::game::version::iw8::v1_20_4_7623265_REPLAY:
				case identification::game::version::iw8::v1_20_4_7623265_SHIP:
					id = IMAGE_SPLASH_v1_20;
					break;
				case identification::game::version::iw8::v1_44_0_10435696:
					id = IMAGE_SPLASH_v1_44;
					break;
				case identification::game::version::iw8::v1_38_3_9489393:
					id = IMAGE_SPLASH_v1_38;
					break;
				default:
					id = IMAGE_SPLASH;
					break;
				}
				return load_image_a_hook.invoke<HANDLE>(client_module, MAKEINTRESOURCEA(id), 0, 0, 0, LR_COPYFROMRESOURCE);
			}

			return load_image_a_hook.invoke<HANDLE>(h_inst, name, type, c_x, c_y, fu_load);
		}
	}

	struct component final : client_component {
		void post_load() override {
			load_image_a_hook.create({}, "user32.dll", "LoadImageA", load_image_a_stub);
		}
	};
}

REGISTER_COMPONENT(splash::component)