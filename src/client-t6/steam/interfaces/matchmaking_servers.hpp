#pragma once

namespace steam {
	typedef enum EMatchMakingServerResponse {
		server_responded = 0,
		server_failed_to_respond,
		no_servers_listed_on_master_server
	} matchmaking_server_response;

	class servernetadr_t {
	public:
		std::uint16_t connection_port_;
		std::uint16_t query_port_;
		std::uint32_t ip_;
	};

	class gameserveritem_t {
	public:
		servernetadr_t netadr_;
		int ping_;
		bool had_successful_response_;
		bool do_not_refresh_;
		char game_dir_[32];
		char map_[32];
		char game_description_[64];
		std::uint32_t app_id_;
		int players_;
		int max_players_;
		int bot_players_;
		bool password_;
		bool secure_;
		std::uint32_t time_last_played_;
		int server_version_;
		char server_name_[64];
		char game_tags_[128];
		steam_id steam_id_;
	};

	class matchmaking_ping_response {
	public:
		virtual void ServerResponded(gameserveritem_t& server) = 0;
		virtual void ServerFailedToRespond() = 0;
	};

	class matchmaking_server_list_response {
	public:
		virtual void ServerResponded(void* hRequest, int iServer) = 0;
		virtual void ServerFailedToRespond(void* hRequest, int iServer) = 0;
		virtual void RefreshComplete(void* hRequest, matchmaking_server_response response) = 0;
	};
	
	class matchmaking_servers {
	public:
		~matchmaking_servers() = default;
		
		virtual void* RequestInternetServerList(std::uint32_t iApp, void** ppchFilters, std::uint32_t nFilters, matchmaking_server_list_response* pRequestServersResponse);
		virtual void* RequestLANServerList(std::uint32_t iApp, matchmaking_server_list_response* pRequestServersResponse);
		virtual void* RequestFriendsServerList(std::uint32_t iApp, void** ppchFilters, std::uint32_t nFilters, matchmaking_server_list_response* pRequestServersResponse);
		virtual void* RequestFavoritesServerList(std::uint32_t iApp, void** ppchFilters, std::uint32_t nFilters, matchmaking_server_list_response* pRequestServersResponse);
		virtual void* RequestHistoryServerList(std::uint32_t iApp, void** ppchFilters, std::uint32_t nFilters, matchmaking_server_list_response* pRequestServersResponse);
		virtual void* RequestSpectatorServerList(std::uint32_t iApp, void** ppchFilters, std::uint32_t nFilters, matchmaking_server_list_response* pRequestServersResponse);
		virtual void ReleaseRequest(void* hServerListRequest);
		virtual gameserveritem_t* GetServerDetails(void* hRequest, int iServer);
		virtual void CancelQuery(void* hRequest);
		virtual void RefreshQuery(void* hRequest);
		virtual bool IsRefreshing(void* hRequest);
		virtual int GetServerCount(void* hRequest);
		virtual void RefreshServer(void* hRequest, int iServer);
		virtual int PingServer(std::uint32_t unIP, std::uint16_t usPort, matchmaking_ping_response* pRequestServersResponse);
		virtual int PlayerDetails(std::uint32_t unIP, std::uint16_t usPort, void* pRequestServersResponse);
		virtual int ServerRules(std::uint32_t unIP, std::uint16_t usPort, void* pRequestServersResponse);
		virtual void CancelServerQuery(int hServerQuery);
	};
}
