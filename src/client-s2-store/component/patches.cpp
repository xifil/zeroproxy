#include "common.hpp"

#include "component/scheduler.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

#include <version.hpp>

namespace patches {
	namespace {
		utils::hook::detour seh_stringed_get_string_hook;

		utils::hook::iat_detour create_window_ex_w_hook;

		const char* seh_stringed_get_string_stub(const char* key) {
			return key;
		}

		HWND create_window_ex_w_stub(DWORD dw_ex_style, LPCWSTR lp_class_name, LPCWSTR lp_window_name, DWORD dw_style, int x, int y, int n_width, int n_height,
			HWND hwnd_parent, HMENU h_menu, HINSTANCE h_instance, LPVOID lp_param)
		{
			LPCWSTR lp_window_name_patched = lp_window_name;
			if (wcscmp(lp_class_name, L"S2") == 0) {
				lp_window_name_patched = L"s2s by lifix and luxploit | " GIT_DESCRIBE;
			}

			return create_window_ex_w_hook.invoke<HWND>(dw_ex_style, lp_class_name, lp_window_name_patched, dw_style, x, y, n_width, n_height, hwnd_parent,
				h_menu, h_instance, lp_param);
		}
	}

	struct component final : generic_component {
		void post_load() override {
			create_window_ex_w_hook.create(utils::nt::library(), "user32.dll", "CreateWindowExW", create_window_ex_w_stub);
		}

		void post_unpack() override {
			seh_stringed_get_string_hook.create(game::SEH_StringEd_GetString, seh_stringed_get_string_stub);
			//x_store_query_game_license_result_hook.create(game::XStoreQueryGameLicenseResult, x_store_query_game_license_result_stub);
		}
	};
}

//REGISTER_COMPONENT(patches::component)