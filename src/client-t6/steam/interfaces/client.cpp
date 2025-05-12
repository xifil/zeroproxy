#include "common.hpp"
#include "steam/steam.hpp"

namespace steam {
	HSteamPipe client::CreateSteamPipe() {
		return 1;
	}

	bool client::BReleaseSteamPipe(HSteamPipe hSteamPipe) {
		return true;
	}

	HSteamUser client::ConnectToGlobalUser(HSteamPipe hSteamPipe) {
		return 1;
	}

	HSteamUser client::CreateLocalUser(HSteamPipe* phSteamPipe, std::uint32_t eAccountType) {
		return 1;
	}

	void client::ReleaseUser(HSteamPipe hSteamPipe, HSteamUser hUser) {}

	void* client::GetISteamUser(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) {
		return SteamUser();
	}

	void* client::GetISteamGameServer(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) {
		return SteamGameServer();
	}

	void client::SetLocalIPBinding(std::uint32_t unIP, std::uint16_t usPort) {}

	void* client::GetISteamFriends(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) {
		return SteamFriends();
	}

	void* client::GetISteamUtils(HSteamPipe hSteamPipe, const char* pchVersion) {
		return SteamUtils();
	}

	void* client::GetISteamMatchmaking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) {
		return SteamMatchmaking();
	}

	void* client::GetISteamMatchmakingServers(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) {
		static matchmaking_servers u;
		return &u;
	}

	void* client::GetISteamGenericInterface(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) {
		return nullptr;
	}

	void* client::GetISteamUserStats(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) {
		return SteamUserStats();
	}

	void* client::GetISteamGameServerStats(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) {
		static game_server_stats u;
		return &u;
	}

	void* client::GetISteamApps(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) {
		return SteamApps();
	}

	void* client::GetISteamNetworking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) {
		return SteamNetworking();
	}

	void* client::GetISteamRemoteStorage(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) {
		return SteamRemoteStorage();
	}

	void* client::GetISteamScreenshots(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) {
		static screenshots s;
		return &s;
	}

	void client::RunFrame() {}

	std::uint32_t client::GetIPCCallCount() {
		return 0;
	}

	void client::SetWarningMessageHook(void* pFunction) {}

	bool client::BShutdownIfAllPipesClosed() {
		return true;
	}

	void* client::GetISteamHTTP(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) {
		static http h;
		return &h;
	}

	void* client::GetISteamUnifiedMessages(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) {
		static unified_messages u;
		return &u;
	}

	void* client::GetISteamController(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion) {
		static controller c;
		return &c;
	}
}