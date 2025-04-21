#include "common.hpp"
#include "steam/steam.hpp"

namespace steam {
	void* matchmaking_servers::RequestInternetServerList(std::uint32_t iApp, void** ppchFilters, std::uint32_t nFilters, matchmaking_server_list_response * pRequestServersResponse) {
		return nullptr;
	}
	
	void* matchmaking_servers::RequestLANServerList(std::uint32_t iApp, matchmaking_server_list_response* pRequestServersResponse) {
		return nullptr;
	}
	
	void* matchmaking_servers::RequestFriendsServerList(std::uint32_t iApp, void** ppchFilters, std::uint32_t nFilters, matchmaking_server_list_response* pRequestServersResponse) {
		return nullptr;
	}
	
	void* matchmaking_servers::RequestFavoritesServerList(std::uint32_t iApp, void** ppchFilters, std::uint32_t nFilters, matchmaking_server_list_response* pRequestServersResponse) {
		return nullptr;
	}
	
	void* matchmaking_servers::RequestHistoryServerList(std::uint32_t iApp, void** ppchFilters, std::uint32_t nFilters, matchmaking_server_list_response* pRequestServersResponse) {
		return nullptr;
	}
	
	void* matchmaking_servers::RequestSpectatorServerList(std::uint32_t iApp, void** ppchFilters, std::uint32_t nFilters, matchmaking_server_list_response* pRequestServersResponse) {
		return nullptr;
	}
	
	void matchmaking_servers::ReleaseRequest(void* hServerListRequest) {}
	
	gameserveritem_t* matchmaking_servers::GetServerDetails(void* hRequest, int iServer) {
		return nullptr;
	}
	
	void matchmaking_servers::CancelQuery(void* hRequest) {}
	
	void matchmaking_servers::RefreshQuery(void* hRequest) {}
	
	bool matchmaking_servers::IsRefreshing(void* hRequest) {
		return false;
	}
	
	int matchmaking_servers::GetServerCount(void* hRequest) {
		return 1;
	}
	
	void matchmaking_servers::RefreshServer(void* hRequest, int iServer) {}
	
	int matchmaking_servers::PingServer(std::uint32_t unIP, std::uint16_t usPort, matchmaking_ping_response* pRequestServersResponse) {
		return 0;
	}

	int matchmaking_servers::PlayerDetails(std::uint32_t unIP, std::uint16_t usPort, void* pRequestServersResponse) {
		return 0;
	}

	int matchmaking_servers::ServerRules(std::uint32_t unIP, std::uint16_t usPort, void* pRequestServersResponse) {
		return 0;
	}

	void matchmaking_servers::CancelServerQuery(int hServerQuery) {}
}
