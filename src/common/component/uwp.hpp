#pragma once
#include "common_core.hpp"

#if defined(_WIN64)
#include "engine/uwp/IStoreImpl6.hpp"
#include "identification/game.hpp"
#include "loader/component_loader.hpp"
#include "logger/logger.hpp"
#include "utils/hook.hpp"
#include "utils/string.hpp"

namespace uwp {
	namespace {
		utils::hook::detour query_api_impl_hook;
		utils::hook::detour x_game_save_files_get_folder_with_ui_result_hook;
		utils::hook::detour x_store_query_game_license_result_hook;
		utils::hook::detour x_user_is_store_user_hook;

		utils::hook::iat_detour get_proc_address_hook;

		std::string guid_to_string(GUID guid) {
			return std::format("{:08x}-{:04x}-{:04x}-{:02x}{:02x}-{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}", guid.Data1, guid.Data2, guid.Data3,
				guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
		}

		bool is_target_api(GUID guid_first, GUID guid_second, const std::string& guid_first_target, const std::string& guid_second_target) {
			return guid_to_string(guid_first) == guid_first_target && guid_to_string(guid_second) == guid_second_target;
		}

		void* get_vt_function(void* class_ptr, std::size_t index) {
			struct vt_cls { void** vftable_; };
			return PTR_AS(vt_cls*, class_ptr)->vftable_[index];
		}

		namespace x_game_save {
			HRESULT x_game_save_files_get_folder_with_ui_result_stub(void* _this, uwp::XAsyncBlock* async, std::size_t folder_size, char* folder_result) {
				if (_getcwd(folder_result, folder_size) == nullptr) {
					return x_game_save_files_get_folder_with_ui_result_hook.invoke<HRESULT>(_this, async, folder_size, folder_result);
				}

				return S_OK;
			}
		}

		namespace x_store {
			HRESULT x_store_query_game_license_result_stub(uwp::IStoreImpl1* _this, uwp::XAsyncBlock* async, uwp::XStoreGameLicense* license) {
				// result ignored, we return S_OK anyway to avoid "popup_drm_menu_gdk_license_error"
				x_store_query_game_license_result_hook.invoke<HRESULT>(_this, async, license);

				// bypass "popup_drm_menu_gdk_invalid_license"
				license->is_active_ = true;
				license->is_disc_license_ = false;
				license->is_trial_ = false;

				return S_OK;
			}
		}

		namespace x_user {
			bool x_user_is_store_user_stub(void* _this, uwp::XUserHandle user) {
				return true;
			}
		}

		HRESULT query_api_impl_stub(GUID* first, GUID* second, void** api_out) {
			auto res = query_api_impl_hook.invoke<HRESULT>(first, second, api_out);
			static bool hooked_game_save_vt = false;
			static bool hooked_store_vt = false;
			static bool hooked_user_vt = false;

			if (first != nullptr && second != nullptr && res >= 0) {
				if (!hooked_game_save_vt && is_target_api(*first, *second, "704c3f58-e629-4cc2-b197-30511b996fe2", "704c3f58-e629-4cc2-b197-30511b996ee2")) {
					if (identification::game::get_target_game() == "Black Ops III"s) {
						x_game_save_files_get_folder_with_ui_result_hook.create(get_vt_function(*api_out, 31),
							x_game_save::x_game_save_files_get_folder_with_ui_result_stub);
					}
					hooked_game_save_vt = true;
				}

				if (!hooked_store_vt && is_target_api(*first, *second, "0dd112ac-7c24-448c-b92b-3960fb5bd30c", "5c48dedf-0b67-4492-a4b5-6829b8e796e1")) {
					x_store_query_game_license_result_hook.create(get_vt_function(*api_out, 29), x_store::x_store_query_game_license_result_stub);
					hooked_store_vt = true;
				}

				if (!hooked_user_vt && is_target_api(*first, *second, "01acd177-91f9-4763-a38e-ccbb55ce32e0", "079415e3-6727-437f-8e9d-8f8f9b2439f7")) {
					x_user_is_store_user_hook.create(get_vt_function(*api_out, 42), x_user::x_user_is_store_user_stub);
					hooked_user_vt = true;
				}
			}
			return res;
		}

		FARPROC get_proc_address_stub(HMODULE h_module, LPCSTR lp_proc_name) {
			auto res = get_proc_address_hook.invoke<FARPROC>(h_module, lp_proc_name);
			utils::nt::library lib(h_module);
			if (lib.is_valid() && utils::string::to_lower(lib.get_name()) == "xgameruntime.dll" && "QueryApiImpl"s == lp_proc_name) {
				/*
				 * no, this cannot be an IAT detour because xgameruntime.dll/QueryApiImpl is not directly imported into the game, but
				 * loaded and imported dynamically after the execution of WinMain, therefore IAT detouring doesn't work and we have to
				 * hook into GetProcAddress instead to hook this function as soon as it is loaded.
				 */
				query_api_impl_hook.create(res, query_api_impl_stub);
			}
			return res;
		}
	}

	struct component final : generic_component {
		void post_load() override {
			utils::nt::library game{};
			if (game.get_iat_entry("XCurl.dll", "curl_multi_poll") == nullptr) {
				return;
			}

			get_proc_address_hook.create(game, "kernel32.dll", "GetProcAddress", get_proc_address_stub);
		}
	};
}
#endif
