#pragma once

namespace steam {
	using HSteamPipe = int;
	using HSteamUser = int;
	
	class client {
	public:
		~client() = default;

		virtual HSteamPipe CreateSteamPipe();
		virtual bool BReleaseSteamPipe(HSteamPipe hSteamPipe);
		virtual HSteamUser ConnectToGlobalUser(HSteamPipe hSteamPipe);
		virtual HSteamUser CreateLocalUser(HSteamPipe* phSteamPipe, std::uint32_t eAccountType);
		virtual void ReleaseUser(HSteamPipe hSteamPipe, HSteamUser hUser);
		virtual void* GetISteamUser(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		virtual void* GetISteamGameServer(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		virtual void SetLocalIPBinding(std::uint32_t unIP, std::uint16_t usPort);
		virtual void* GetISteamFriends(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		virtual void* GetISteamUtils(HSteamPipe hSteamPipe, const char* pchVersion);
		virtual void* GetISteamMatchmaking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		virtual void* GetISteamMatchmakingServers(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		virtual void* GetISteamGenericInterface(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		virtual void* GetISteamUserStats(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		virtual void* GetISteamGameServerStats(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		virtual void* GetISteamApps(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		virtual void* GetISteamNetworking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		virtual void* GetISteamRemoteStorage(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		virtual void* GetISteamScreenshots(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		virtual void RunFrame();
		virtual std::uint32_t GetIPCCallCount();
		virtual void SetWarningMessageHook(void* pFunction);
		virtual bool BShutdownIfAllPipesClosed();
		virtual void* GetISteamHTTP(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		virtual void* GetISteamUnifiedMessages(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		virtual void* GetISteamController(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
	};
}
