#pragma once
#include "common.hpp"

struct raw_steam_id final {
	unsigned int account_id : 32;
	unsigned int account_instance : 20;
	unsigned int account_type : 4;
	int universe : 8;
};

typedef union {
	raw_steam_id raw;
	unsigned long long bits;
} steam_id;

#pragma pack(push, 1)
struct raw_game_id final {
	unsigned int app_id : 24;
	unsigned int type : 8;
	unsigned int mod_id : 32;
};

typedef union {
	raw_game_id raw;
	unsigned long long bits;
} game_id;
#pragma pack(pop)

#include "steam/interfaces/apps.hpp"
#include "steam/interfaces/client.hpp"
#include "steam/interfaces/content_server.hpp"
#include "steam/interfaces/controller.hpp"
#include "steam/interfaces/friends.hpp"
#include "steam/interfaces/game_server_stats.hpp"
#include "steam/interfaces/http.hpp"
#include "steam/interfaces/matchmaking.hpp"
#include "steam/interfaces/matchmaking_servers.hpp"
#include "steam/interfaces/networking.hpp"
#include "steam/interfaces/remote_storage.hpp"
#include "steam/interfaces/screenshots.hpp"
#include "steam/interfaces/unified_messages.hpp"
#include "steam/interfaces/user.hpp"
#include "steam/interfaces/user_stats.hpp"
#include "steam/interfaces/utils.hpp"

namespace steam {
	class callbacks {
	public:
		class base {
		public:
			base()
				: flags_(0)
				, callback_(0)
			{}

			virtual void run(void* pv_param) = 0;
			virtual void run(void* pv_param, bool failure, std::uint64_t handle) = 0;
			virtual int get_callback_size_bytes() = 0;

			int get_i_callback() const {
				return callback_;
			}

			void set_i_callback(const int i_callback) {
				callback_ = i_callback;
			}

		protected:
			~base() = default;

			unsigned char flags_;
			int callback_;
		};

		struct result final {
			void* data{};
			int size{};
			int type{};
			std::uint64_t call{};
		};

		static std::uint64_t register_call();

		static void register_callback(base* handler, int callback);
		static void unregister_callback(base* handler);

		static void register_call_result(std::uint64_t call, base* result);
		static void unregister_call_result(std::uint64_t call, base* result);

		static void return_call(void* data, int size, int type, std::uint64_t call);
		static void run_callbacks();

	private:
		static std::uint64_t call_id_;
		static std::recursive_mutex mutex_;
		static std::map<std::uint64_t, bool> calls_;
		static std::map<std::uint64_t, base*> result_handlers_;
		static std::vector<result> results_;
		static std::vector<base*> callback_list_;
	};

	void patch_iat_entries();

	bool SteamAPI_RestartAppIfNecessary();
	bool SteamAPI_Init();
	void SteamAPI_RegisterCallResult(callbacks::base* result, std::uint64_t call);
	void SteamAPI_RegisterCallback(callbacks::base* handler, int callback);
	void SteamAPI_RunCallbacks();
	void SteamAPI_Shutdown();
	void SteamAPI_UnregisterCallResult(callbacks::base* result, const std::uint64_t call);
	void SteamAPI_UnregisterCallback(callbacks::base* handler);
	const char* SteamAPI_GetSteamInstallPath();

	void* SteamGameServer_GetHSteamPipe();
	void* SteamGameServer_GetHSteamUser();

	void* SteamAPI_GetHSteamUser();
	void* SteamAPI_GetHSteamPipe();

	void* SteamInternal_CreateInterface(const char* interface_name);

	bool SteamInternal_GameServer_Init();
	bool SteamGameServer_Init();
	void SteamGameServer_RunCallbacks();
	void SteamGameServer_Shutdown();

	friends* SteamFriends();
	matchmaking* SteamMatchmaking();
	void* SteamGameServer();
	networking* SteamNetworking();
	remote_storage* SteamRemoteStorage();
	user* SteamUser();
	utils* SteamUtils();
	apps* SteamApps();
	user_stats* SteamUserStats();
}
