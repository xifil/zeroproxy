#include "common.hpp"

#include "component/scheduler.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

#include <version.hpp>

namespace patches {
	namespace {
		utils::hook::detour x_store_query_game_license_result_hook;

		utils::hook::iat_detour create_window_ex_a_hook;

		HRESULT x_store_query_game_license_result_stub(void* async, uwp::XStoreGameLicense* license) {
			// result ignored, we return S_OK anyway to avoid "popup_drm_menu_gdk_license_error"
			x_store_query_game_license_result_hook.invoke<HRESULT>(async, license);

			// bypass "popup_drm_menu_gdk_invalid_license"
			license->is_active_ = true;
			license->is_disc_license_ = false;
			license->is_trial_ = false;

			return S_OK;
		}

		HWND create_window_ex_a_stub(DWORD dw_ex_style, LPCSTR lp_class_name, LPCSTR lp_window_name, DWORD dw_style, int x, int y, int n_width, int n_height,
			HWND hwnd_parent, HMENU h_menu, HINSTANCE h_instance, LPVOID lp_param)
		{
			LPCSTR lp_window_name_patched = lp_window_name;
			if (strcmp(lp_class_name, "CoDBlackOps") == 0) {
				lp_window_name_patched = "t6s by lifix and luxploit | " GIT_DESCRIBE;
			}

			return create_window_ex_a_hook.invoke<HWND>(dw_ex_style, lp_class_name, lp_window_name_patched, dw_style, x, y, n_width, n_height, hwnd_parent,
				h_menu, h_instance, lp_param);
		}
	}

	struct component final : generic_component {
		void post_load() override {
			x_store_query_game_license_result_hook.create(game::XStoreQueryGameLicenseResult, x_store_query_game_license_result_stub);
			
			create_window_ex_a_hook.create(utils::nt::library(), "user32.dll", "CreateWindowExA", create_window_ex_a_stub);
		}
	};
}

REGISTER_COMPONENT(patches::component)