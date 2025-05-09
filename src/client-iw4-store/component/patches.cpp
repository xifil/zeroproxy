#include "common.hpp"

#include "component/localized_strings.hpp"
#include "component/scheduler.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>
#include <utils/string.hpp>

#include <version.hpp>

namespace patches {
	namespace {
		utils::hook::detour initialize_api_impl_hook;
		utils::hook::detour initialize_api_impl_ex_hook;
		utils::hook::detour query_api_impl_hook;
		utils::hook::detour x_store_query_game_license_result_hook;

		utils::hook::iat_detour create_window_ex_a_hook;
		utils::hook::iat_detour get_proc_address_hook;

		HRESULT initialize_api_impl_stub(std::uint64_t a1, std::uint64_t a2) {
			LOG("Component/Patches", DEBUG, "[" __FUNCTION__ "](0x{:016X}, 0x{:016X})", a1, a2);
			return initialize_api_impl_hook.invoke<HRESULT>(a1, a2);
		}

		HRESULT initialize_api_impl_ex_stub(std::uint64_t a1, std::uint64_t a2, std::uint64_t a3) {
			LOG("Component/Patches", DEBUG, "[" __FUNCTION__ "](0x{:016X}, 0x{:016X}, 0x{:016X})", a1, a2, a3);
			return initialize_api_impl_ex_hook.invoke<HRESULT>(a1, a2, a3);
		}

		HRESULT query_api_impl_stub(std::uint64_t a1, std::uint64_t a2, std::uint64_t a3) {
			LOG("Component/Patches", DEBUG, "[" __FUNCTION__ "]({}, {}, {})", and_rel(a1), and_rel(a2), and_rel(a3));
			return query_api_impl_hook.invoke<HRESULT>(a1, a2, a3);
		}

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
			if (strcmp(lp_class_name, "IW4") == 0) {
				lp_window_name_patched = "iw4s by lifix and luxploit | " GIT_DESCRIBE;
			}

			return create_window_ex_a_hook.invoke<HWND>(dw_ex_style, lp_class_name, lp_window_name_patched, dw_style, x, y, n_width, n_height, hwnd_parent,
				h_menu, h_instance, lp_param);
		}

		FARPROC get_proc_address_stub(HMODULE h_module, LPCSTR lp_proc_name) {
			auto res = get_proc_address_hook.invoke<FARPROC>(h_module, lp_proc_name);
			utils::nt::library lib(h_module);
			if (lib.is_valid() && utils::string::to_lower(lib.get_name()) == "xgameruntime.dll") {
				LOG("Component/Patches", DEBUG, "GetProcAddr: {}/{} = {}", lib.get_name(), lp_proc_name, and_rel(PTR_AS(std::uintptr_t, res)));
				if ("InitializeApiImpl"s == lp_proc_name) {
					initialize_api_impl_hook.create(res, initialize_api_impl_stub);
				}
				else if ("InitializeApiImplEx"s == lp_proc_name) {
					initialize_api_impl_ex_hook.create(res, initialize_api_impl_ex_stub);
				}
				else if ("QueryApiImpl"s == lp_proc_name) {
					query_api_impl_hook.create(res, query_api_impl_stub);
				}
			}
			return res;
		}
	}

	struct component final : generic_component {
		void post_load() override {
			x_store_query_game_license_result_hook.create(game::XStoreQueryGameLicenseResult, x_store_query_game_license_result_stub);
			
			create_window_ex_a_hook.create(utils::nt::library(), "user32.dll", "CreateWindowExA", create_window_ex_a_stub);
			get_proc_address_hook.create(utils::nt::library(), "kernel32.dll", "GetProcAddress", get_proc_address_stub);

			/*
			localized_strings::override(std::regex(".*"), [](const localized_strings::original_localization& original, const std::smatch&) {
				//return std::format("{} ({})", original.text_, original.translation_key_);
				return std::format("hi lifix, {}", original.translation_key_);
			});
			*/
		}
	};
}

REGISTER_COMPONENT(patches::component)