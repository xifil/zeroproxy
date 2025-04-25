#include "common.hpp"
#include "component/scheduler.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>

#include <discord_rpc.h>
#include <ctime>

namespace discord {
	namespace {
		bool is_in_frontend() {
			return game::s_luaInFrontend == nullptr || *game::s_luaInFrontend;
		}
	
		const char* get_map_name(const char* map) {
			iw8::mapInfo* info = game::Com_GameInfo_GetMapInfoForLoadName(map);
			if (!info) {
				return "Unknown Map";
			}
			if (info->map_name_[0] == '\x1F') {
				return "error";
			}
			return game::SEH_StringEd_GetString(info->map_name_);
		}

		const char* get_game_type_name(const char* game_type) {
			iw8::gameTypeInfo* info = game::Com_GameInfo_GetGameTypeForInternalName(game_type);
			if (!info) {
				return "Unknown Mode";
			}
			if (info->game_type_name_[0] == '\x1F') {
				return "error";
			}
			return game::SEH_StringEd_GetString(info->game_type_name_);
		}
		
		void ready(const DiscordUser* request) {
			SetEnvironmentVariableA("discord_user", request->userId);

			LOG("Component/Discord", INFO, "Ready: {} - {}", request->userId, request->username);

			DiscordRichPresence discord_presence{};
			ZeroMemory(&discord_presence, sizeof(discord_presence));

			discord_presence.instance = 1;

			discord_presence.partySize = 0;
			discord_presence.partyMax = 0;
			discord_presence.startTimestamp = time(nullptr);
			discord_presence.largeImageKey = "mw";
			discord_presence.smallImageKey = "";
			discord_presence.details = "...";

			Discord_UpdatePresence(&discord_presence);
		}

		void errored(const int error_code, const char* message) {
			LOG("Component/Discord", ERROR, "{}: {}", error_code, message);
		}

		void update() {
			DiscordRichPresence discord_presence;
			ZeroMemory(&discord_presence, sizeof(discord_presence));

			discord_presence.instance = 1;
			discord_presence.startTimestamp = time(nullptr);

			discord_presence.partySize = game::Dvar_GetIntSafe("NKSQNMMRRQ" /* party_partyPlayerCountNum */);
			discord_presence.partyMax = game::Dvar_GetIntSafe("OOTQKOTRM" /* party_maxplayers */);

			discord_presence.button1name = "Discord";
			discord_presence.button1link = "https://discord.gg/dPzJajt";

			if (is_in_frontend()) {
				discord_presence.details = discord_presence.largeImageText = "In Menus";
				discord_presence.state = discord_presence.smallImageText = "Waiting";
				discord_presence.largeImageKey = "mw";
				discord_presence.smallImageKey = "";
			}
			else {
				const char* map = game::Dvar_GetStringSafe("NSQLTTMRMP" /* ui_mapname */);
				const char* game_type = game::Dvar_GetStringSafe("MOLPOSLOMO" /* ui_gametype */);

				discord_presence.details = discord_presence.largeImageText = get_map_name(map);
				discord_presence.state = discord_presence.smallImageText = get_game_type_name(game_type);
				discord_presence.largeImageKey = map;
				discord_presence.smallImageKey = game_type;
			}

			Discord_UpdatePresence(&discord_presence);
		}

		void update_thread() {
			static bool was_in_frontend = is_in_frontend();
			bool in_frontend = is_in_frontend();
			if (was_in_frontend != in_frontend) {
				update();
				was_in_frontend = in_frontend;
			}
		}
	}

	class component final : public client_component {
	public:
		void post_load() override {
			DiscordEventHandlers handlers;
			ZeroMemory(&handlers, sizeof(handlers));
			handlers.ready = ready;
			handlers.errored = errored;
			handlers.disconnected = errored;
			handlers.joinGame = nullptr;
			handlers.spectateGame = nullptr;
			handlers.joinRequest = nullptr;

			Discord_Initialize("1315310787010498592", &handlers, true, nullptr);

			this->initialized_ = true;

			scheduler::loop(Discord_RunCallbacks, scheduler::pipeline::async, 1s);
		}

		void post_unpack() override {
			scheduler::loop(update_thread, scheduler::pipeline::async, 1s);
		}

		void pre_destroy() override {
			if (this->initialized_) {
				Discord_Shutdown();
			}
		}

	private:
		bool initialized_ = false;
	};
}

//REGISTER_COMPONENT(discord::component)