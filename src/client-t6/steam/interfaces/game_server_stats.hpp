#pragma once

namespace steam {
	class game_server_stats {
	public:
		~game_server_stats() = default;

		virtual std::uint64_t RequestUserStats(steam_id steamIDUser);
		virtual bool GetUserStat(steam_id steamIDUser, const char* pchName, int* pData);
		virtual bool GetUserStat(steam_id steamIDUser, const char* pchName, float* pData);
		virtual bool GetUserAchievement(steam_id steamIDUser, const char* pchName, bool* pbAchieved);
		virtual bool SetUserStat(steam_id steamIDUser, const char* pchName, int nData);
		virtual bool SetUserStat(steam_id steamIDUser, const char* pchName, float fData);
		virtual bool UpdateUserAvgRateStat(steam_id steamIDUser, const char* pchName, float flCountThisSession, double dSessionLength);
		virtual bool SetUserAchievement(steam_id steamIDUser, const char* pchName);
		virtual bool ClearUserAchievement(steam_id steamIDUser, const char* pchName);
		virtual std::uint64_t StoreUserStats(steam_id steamIDUser);
	};
}
