#include "common.hpp"
#include "component/steam_proxy.hpp"

#include <loader/component_loader.hpp>
#include <utils/nt.hpp>
#include <utils/flags.hpp>
#include <utils/string.hpp>
#include <utils/finally.hpp>
#include <utils/concurrency.hpp>

#include "steam/interface.hpp"
#include "steam/steam.hpp"

#include "component/scheduler.hpp"

namespace steam_proxy {
	namespace {
		utils::nt::library steam_client_module{};
		utils::nt::library steam_overlay_module{};

		steam::HSteamPipe steam_pipe = 0;
		steam::HSteamUser global_user = 0;

		steam::interface client_engine{};
		steam::interface client_user{};
		steam::interface client_utils{};
		steam::interface client_friends{};

		steam::client* steam_client{};

		enum class ownership_state {
			success,
			unowned,
			nosteam,
			error,
		};

		bool is_disabled() {
			static const auto disabled = utils::flags::has_flag("nosteam");
			return disabled;
		}

		void* load_client_engine() {
			if (!steam_client_module) {
				return nullptr;
			}

			for (auto i = 1; i <= 999; ++i) {
				std::string name = utils::string::va("CLIENTENGINE_INTERFACE_VERSION%03i", i);
				if (auto* const temp_client_engine = steam_client_module.invoke<void*>("CreateInterface", name.data(), nullptr)) {
					return temp_client_engine;
				}
			}

			return nullptr;
		}

		void load_client() {
			SetEnvironmentVariableA("SteamAppId", std::to_string(steam::SteamUtils()->GetAppID()).data());

			const std::filesystem::path steam_path = steam::SteamAPI_GetSteamInstallPath();
			if (steam_path.empty()) {
				return;
			}

			utils::nt::library::load(steam_path / "tier0_s.dll");
			utils::nt::library::load(steam_path / "vstdlib_s.dll");
			steam_overlay_module = utils::nt::library::load(steam_path / "gameoverlayrenderer.dll");
			steam_client_module = utils::nt::library::load(steam_path / "steamclient.dll");
			if (!steam_client_module) {
				return;
			}

			client_engine = load_client_engine();
			if (!client_engine) {
				return;
			}

			steam_pipe = steam_client_module.invoke<steam::HSteamPipe>("Steam_CreateSteamPipe");
			global_user = steam_client_module.invoke<steam::HSteamUser>("Steam_ConnectToGlobalUser", steam_pipe);

			client_user = client_engine.invoke<void*>(8, global_user, steam_pipe);
			client_utils = client_engine.invoke<void*>(14, steam_pipe);
			client_friends = client_engine.invoke<void*>(13, global_user, steam_pipe);
		}

		void do_cleanup() {
			client_engine = nullptr;
			client_user = nullptr;
			client_utils = nullptr;
			client_friends = nullptr;

			steam_pipe = 0;
			global_user = 0;

			steam_client = nullptr;
		}

		bool perform_cleanup_if_needed() {
			if (steam_client) {
				return true;
			}

			if (steam_client_module && steam_pipe && global_user
				&& steam_client_module.invoke<bool>("Steam_BConnected", global_user, steam_pipe)
				&& steam_client_module.invoke<bool>("Steam_BLoggedOn", global_user, steam_pipe))
			{
				return false;
			}

			do_cleanup();
			return true;
		}

		void clean_up_on_error() {
			return scheduler::schedule([] {
				if (perform_cleanup_if_needed()) {
					return scheduler::cond_end;
				}

				return scheduler::cond_continue;
			}, scheduler::pipeline::main);
		}

		ownership_state start_mod_unsafe(const std::string& title, std::size_t app_id) {
			/*
			if (!client_utils || !client_user) {
				return ownership_state::nosteam;
			}

			if (!client_user.invoke<bool>("BIsSubscribedApp", app_id)) {
#				ifdef DEV_BUILD
					app_id = 480; // Spacewar
#				else
					return ownership_state::unowned;
#				endif
			}

			if (is_disabled()) {
				return ownership_state::success;
			}

			client_utils.invoke<void>("SetAppIDForCurrentPipe", app_id, false);

			char our_directory[MAX_PATH] = { 0 };
			GetCurrentDirectoryA(sizeof(our_directory), our_directory);

			const auto game = utils::nt::library{};
			const auto path = game.get_path();
			const auto* cmdline = utils::string::va("\"%s\" -proc %d", path.generic_string().data(), GetCurrentProcessId());

			LOG("Component/SteamProxy", DEBUG, "CurDir = {}", our_directory);
			LOG("Component/SteamProxy", DEBUG, "cmdline = {}", cmdline);

			steam::game_id game_id;
			game_id.raw.type = 1; // k_EGameIDTypeGameMod
			game_id.raw.app_id = app_id & 0xFFFFFF;

			const auto* mod_id = "2012";
			game_id.raw.mod_id = *reinterpret_cast<const unsigned int*>(mod_id) | 0x80000000;

			//client_user.invoke<bool>("SpawnProcess", path.generic_string().data(), cmdline, our_directory, &game_id.bits, title.data(), 0, 0, 0);
			try {
				client_user.invoke<bool>("SpawnProcess", path.generic_string().data(), cmdline, our_directory, game_id.bits, title.data(), app_id, 0, 0, 0);
			}
			catch (std::exception& e) {
				LOG("Component/SteamProxy", ERROR, "SpawnProcess failed with error: {}", e.what());
				return ownership_state::error;
			}
			*/

			/*
			 * As of April 2, 2025, Valve has removed SpawnProcess from the IClientUser interface, rendering the custom Steam presence of any mod (even FiveM for
			 * Grand Theft Auto V) now defunct. No clients or mods have custom presence anymore.
			 */

			return ownership_state::success;
		}

		ownership_state start_mod(const std::string& title, const std::size_t app_id) {
			__try {
				return start_mod_unsafe(title, app_id);
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {
				do_cleanup();
				return ownership_state::error;
			}
		}

		void evaluate_ownership_state(const ownership_state state) {
#			if defined(DEV_BUILD) || defined(NO_CHECK)
				(void)state;
#			else
				switch (state) {
				case ownership_state::nosteam:
					//throw std::runtime_error("Steam must be running to play this game!");
				case ownership_state::unowned:
					//throw std::runtime_error("You must own the game on steam to play this mod!");
				case ownership_state::error:
					//throw std::runtime_error("Failed to verify ownership of the game!");
				case ownership_state::success:
					break;
				}
#			endif
		}
	}

	struct component final : client_component {
		void post_load() override {
			steam::patch_iat_entries();
		
			load_client();
			perform_cleanup_if_needed();

			const auto res = start_mod("\xE2\x98\x84\xEF\xB8\x8F" " New Super t6-mod U Deluxe"s, steam::SteamUtils()->GetAppID());
			if (res == ownership_state::error) {
				LOG("Component/SteamProxy", WARN, "Failed to initialize Steam presence.");
			}
			evaluate_ownership_state(res);
			return clean_up_on_error();
		}

		void pre_destroy() override {
			if (steam_client) {
				if (global_user) {
					return steam_client->ReleaseUser(steam_pipe, global_user);
				}

				return (void)steam_client->BReleaseSteamPipe(steam_pipe);
			}
			else if (steam_client_module && steam_pipe) {
				if (global_user) {
					return steam_client_module.invoke<void>("Steam_ReleaseUser", steam_pipe, global_user);
				}

				return (void)steam_client_module.invoke<bool>("Steam_BReleaseSteamPipe", steam_pipe);
			}
		}

		component_priority priority() const override {
			return component_priority::steam_proxy;
		}
	};

	const utils::nt::library& get_overlay_module() {
		return steam_overlay_module;
	}

	const char* get_player_name() {
		if (client_friends) {
			return client_friends.invoke<const char*>("GetPersonaName");
		}

		return "";
	}

	void initialize() {
		if (client_engine || !steam_client_module) {
			return;
		}

		steam_client = steam_client_module.invoke<steam::client*>("CreateInterface", "SteamClient012", nullptr);
		if (!steam_client) {
			return;
		}

		steam_pipe = steam_client->CreateSteamPipe();
		global_user = steam_client->ConnectToGlobalUser(steam_pipe);
	}
}

REGISTER_COMPONENT(steam_proxy::component)
