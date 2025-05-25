#include "common.hpp"

#include "component/lua_hook.hpp"
#include "component/scheduler.hpp"
#include "game/game.hpp"

#include <component/localized_strings.hpp>
#include <engine/msvc/thread_name_info.hpp>
#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

#include <version.hpp>

namespace patches {
	namespace {
		utils::hook::detour dvar_register_bool_hook;
		utils::hook::detour lua_shared_lua_call_is_demo_build_hook;
		utils::hook::detour lui_cod_lua_call_is_battle_net_auth_ready_hook;
		utils::hook::detour lui_cod_lua_call_is_battle_net_lan_only_hook;
		utils::hook::detour lui_cod_lua_call_is_connected_to_game_server_hook;
		utils::hook::detour lui_cod_lua_call_is_game_mode_allowed_hook;
		utils::hook::detour lui_cod_lua_call_is_game_mode_available_hook;
		utils::hook::detour lui_cod_lua_call_is_premium_player_hook;
		utils::hook::detour lui_cod_lua_call_is_premium_player_ready_hook;
		utils::hook::detour sub_142adf070_hook;
		utils::hook::detour sv_update_user_info_f_hook;
		utils::hook::detour unk_is_unsupported_gpu_hook;

		utils::hook::iat_detour raise_exception_hook;

		iw8::dvar_t* dvar_register_bool_stub(const char* dvar_name, bool value, std::uint32_t flags, const char* description) {
			static std::map<std::pair<std::string, std::string>, bool> dvars_to_patch = {
				{ { "cg_drawBuildName", "LSSSQMQPNL" }, true },
				{ { "cg_drawFastfileDebugInfo", "MOSSSSTTNL" }, true },
				{ { "cg_drawFPS", "OLNTNRTPPL" }, true },
				{ { "cg_drawFrontendSceneDebugInfo", "OMPMKKTORN" }, true },
				{ { "cg_viewedSplashScreen", "MLNMPQOON" }, true },
				{ { "cl_waterMarkEnabled", "LRKNROSQPM" }, true },
				{ { "com_checkIfGameModeInstalled", "RLSPOOTTT" }, false },
				{ { "com_force_premium", "MROLPRPTPO" }, true },
				{ { "com_lan_lobby_enabled", "LPNMMPKRL" }, true },
				{ { "con_bindableGrave", "OKLQKPPKPQ" }, false },
				{ { "con_minicon", "LMSLLSMONN" }, true },
				{ { "force_offline_enabled", "MPSSOTQQPM" }, true },
				{ { "force_offline_menus", "LSTQOKLTRN" }, true },
				{ { "lui_cod_points_enabled", "LNTOKPTKS" }, false },
				{ { "lui_enable_magma_blade_layout", "LRKPTLNQTT" }, false },
				{ { "lui_force_online_menus", "LMMRONPQMO" }, false },
				{ { "lui_wz_tutorial_optional", "LSPSKLPNQT" }, true },
				{ { "online_lan_cross_play", "LTOQRQMMLQ" }, true },
				{ { "ui_onlineRequired", "MTSTMKPMRM" }, false }
			};

			bool value_patched = value;
			std::uint32_t flags_patched = flags;
			for (const auto& [names, val] : dvars_to_patch) {
				if (names.second == dvar_name) {
					const char* disclaimer = "";
					if (value_patched == val) {
						disclaimer = " - unnecessary";
					}
					LOG("Component/Patches/Dvar_RegisterBool", INFO, "Patched '{}' -> {}{}", names.first, val ? "true" : "false", disclaimer);
					value_patched = val;
				}
			}

			if ("LPSPMQSNPQ"s == dvar_name) {
				LOG("Component/Patches/Dvar_RegisterBool", INFO, "Patched 'systemlink' flags");
				flags_patched = 0x80;
			}

			return dvar_register_bool_hook.invoke<iw8::dvar_t*>(dvar_name, value_patched, flags_patched, description);
		}

		/*
		 * seems like a 1.46 exclusive thing - can't seem to find occurrences of this function in any previous version, so I couldn't find the name of it, the
		 * parameter provided, or the structures used.
		 */
		std::uintptr_t sub_142adf070_stub(std::uintptr_t a1) {
			class a1_cls_2 {
			private:
				char pad_0000[0x03D0];	// 0x0000
			public:
				void* var1_;			// 0x03D0
			};

			class a1_cls {
			private:
				char pad_0000[0x0008];	// 0x0000
			public:
				a1_cls_2* var1_;		// 0x0008
			};

			a1_cls* a1_c = PTR_AS(a1_cls*, a1);
			if (a1_c->var1_ == nullptr || a1_c->var1_->var1_ == nullptr) {
				LOG("Component/Patches", DEBUG, "Calling 0x2adf070({}) -> {} -> null checked", and_rel(a1), and_rel(PTR_AS(std::uintptr_t, _ReturnAddress())));
				return 0;
			}

			return sub_142adf070_hook.invoke<std::uintptr_t>(a1);
		}

		void sv_update_user_info_f_stub(iw8::SvClientMP* cl) {
			/*
				More checks can be added here

				It's patched in:
					- Modern Warfare (2019) (Current version)
					- Vanguard
					- Modern Warfare II

				Could probably find the actual fix there
			*/
			if (!strlen(game::Info_ValueForKey(game::SV_Cmd_Argv(1), "platform"))) {
				return;
			}

			return sv_update_user_info_f_hook.invoke<void>(cl);
		}

		bool unk_is_unsupported_gpu_stub() {
			return false;
		}

		void mystery_function_stub() {
			return ;
			// do nothing
		}

		void raise_exception_stub(std::uint32_t exception_code_in, std::uint32_t exception_flags, std::uint32_t number_of_arguments,
			const std::uint64_t* arguments)
		{
			LOG("Component/Patches", DEBUG, "Raising exception: 0x{:08X} (fl:0x{:08X}, na:0x{:08X}) and returning to {}",
				exception_code_in, exception_flags, number_of_arguments, and_rel(PTR_AS(std::uintptr_t, _ReturnAddress())));

			if (exception_code_in == 0x1337 || exception_code_in == 0x1338) {
				LOG("Component/Patches", DEBUG, "RaiseException/DebugException -> Ignoring 0x{:08X} exception so we're chill", exception_code_in);
				return;
			}

			if (exception_code_in == 0x406D1388) {
				auto thread_name_info_in = PTR_AS(const msvc::thread_name_info*, arguments);
				LOG("Component/Patches", DEBUG, "RaiseException/SetThreadName -> Setting name of thread with ID {} to {}",
					thread_name_info_in->thread_id_, thread_name_info_in->name_ ? thread_name_info_in->name_ : "<null>");
			}

			return raise_exception_hook.invoke<void>(exception_code_in, exception_flags, number_of_arguments, arguments);
		}

		int lua_return_true_stub(iw8::lua_State* lua_vm) {
			game::lua_pushboolean(lua_vm, TRUE);
			return 1;
		}
	}

	struct component final : generic_component {
		void post_load() override {
			// stop the game from crashing on launch by skipping this one function - still unclear what it actually does.
			switch (identification::game::get_version()) {
			case iw8_version::v1_20_4_7623265_REPLAY:
				utils::hook::set(0x2352548_b, mystery_function_stub);
				break;
			case iw8_version::v1_20_4_7623265_SHIP:
				utils::hook::set(0x3DF4548_b, mystery_function_stub);
				break;
			default:
				LOG("Component/Patches", WARN, "Failed to patch \"mystery function\" - if you're on Windows 11, there is a crash most likely imminent.");
				break;
			}

			raise_exception_hook.create({}, "kernel32.dll", "RaiseException", raise_exception_stub);

			lua_hook::create(lua_shared_lua_call_is_demo_build_hook, "Engine.BGAAHHAGAC", lua_return_true_stub);
			lua_hook::create(lui_cod_lua_call_is_battle_net_auth_ready_hook, "Engine.JBIHDJBH", lua_return_true_stub);
			lua_hook::create(lui_cod_lua_call_is_battle_net_lan_only_hook, "Engine.BJGAADIDFH", lua_return_true_stub);
			lua_hook::create(lui_cod_lua_call_is_connected_to_game_server_hook, "Engine.DHEJECBEE", lua_return_true_stub);
			lua_hook::create(lui_cod_lua_call_is_game_mode_allowed_hook, "Engine.CEGDBDIIIE", lua_return_true_stub);
			lua_hook::create(lui_cod_lua_call_is_game_mode_available_hook, "Engine.DBEGJIECGB", lua_return_true_stub);
			lua_hook::create(lui_cod_lua_call_is_premium_player_hook, "Engine.CFHBIHABCB", lua_return_true_stub);
			lua_hook::create(lui_cod_lua_call_is_premium_player_ready_hook, "Engine.ECFHDAEIDA", lua_return_true_stub);
		}

		void post_unpack() override {
			dvar_register_bool_hook.create(game::Dvar_RegisterBool, dvar_register_bool_stub);
			sv_update_user_info_f_hook.create(game::SV_UpdateUserinfo_f, sv_update_user_info_f_stub);

			if (game::unk_IsUnsupportedGPU) {
				unk_is_unsupported_gpu_hook.create(game::unk_IsUnsupportedGPU, unk_is_unsupported_gpu_stub);
			}

			if (identification::game::is(iw8_version::v1_46_0_10750827)) {
				sub_142adf070_hook.create(0x2ADF070_b, sub_142adf070_stub);
			}
		}
	};
}

REGISTER_COMPONENT(patches::component)