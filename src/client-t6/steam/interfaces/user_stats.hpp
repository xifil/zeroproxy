#pragma once

namespace steam {
	class user_stats {
	public:
		~user_stats() = default;

		virtual bool RequestCurrentStats();
		virtual bool GetStat(const char* pchName, int* pData);
		virtual bool GetStat(const char* pchName, float* pData);
		virtual bool SetStat(const char* pchName, int nData);
		virtual bool SetStat(const char* pchName, float fData);
		virtual bool UpdateAvgRateStat(const char* pchName, float flCountThisSession, double dSessionLength);
		virtual bool GetAchievement(const char* pchName, bool* pbAchieved);
		virtual bool SetAchievement(const char* pchName);
		virtual bool ClearAchievement(const char* pchName);
		virtual bool GetAchievementAndUnlockTime(const char* pchName, bool* pbAchieved, std::uint32_t* punUnlockTime);
		virtual bool StoreStats();
		virtual int GetAchievementIcon(const char* pchName);
		virtual const char* GetAchievementDisplayAttribute(const char* pchName, const char* pchKey);
		virtual bool IndicateAchievementProgress(const char* pchName, std::uint32_t nCurProgress, std::uint32_t nMaxProgress);
		virtual std::uint32_t GetNumAchievements(game_id nGameID);
		virtual const char* GetAchievementName(std::uint32_t iAchievement);
		virtual std::uint64_t RequestUserStats(steam_id steamIDUser);
		virtual bool GetUserStat(steam_id steamIDUser, const char* pchName, int* pData);
		virtual bool GetUserStat(steam_id steamIDUser, const char* pchName, float* pData);
		virtual bool GetUserAchievement(steam_id steamIDUser, const char* pchName, bool* pbAchieved);
		virtual bool GetUserAchievementAndUnlockTime(steam_id steamIDUser, const char* pchName, bool* pbAchieved, std::uint32_t* punUnlockTime);
		virtual bool ResetAllStats(bool bAchievementsToo);
		virtual std::uint64_t FindOrCreateLeaderboard(const char* pchLeaderboardName, int eLeaderboardSortMethod, int eLeaderboardDisplayType);
		virtual std::uint64_t FindLeaderboard(const char* pchLeaderboardName);
		virtual const char* GetLeaderboardName(std::uint64_t hSteamLeaderboard);
		virtual int GetLeaderboardEntryCount(std::uint64_t hSteamLeaderboard);
		virtual int GetLeaderboardSortMethod(std::uint64_t hSteamLeaderboard);
		virtual int GetLeaderboardDisplayType(std::uint64_t hSteamLeaderboard);
		virtual std::uint64_t DownloadLeaderboardEntries(std::uint64_t hSteamLeaderboard, int eLeaderboardDataRequest, int nRangeStart, int nRangeEnd);
		virtual std::uint64_t DownloadLeaderboardEntriesForUsers(std::uint64_t hSteamLeaderboard, steam_id* prgUsers, int cUsers);
		virtual bool GetDownloadedLeaderboardEntry(std::uint64_t hSteamLeaderboardEntries, int index, int* pLeaderboardEntry, int* pDetails, int cDetailsMax);
		virtual std::uint64_t UploadLeaderboardScore(std::uint64_t hSteamLeaderboard, int eLeaderboardUploadScoreMethod, int nScore, const int* pScoreDetails, int cScoreDetailsCount);
		virtual std::uint64_t AttachLeaderboardUGC(std::uint64_t hSteamLeaderboard, std::uint64_t hUGC);
		virtual std::uint64_t GetNumberOfCurrentPlayers();
		virtual std::uint64_t RequestGlobalAchievementPercentages();
		virtual int GetMostAchievedAchievementInfo(char* pchName, std::uint32_t unNameBufLen, float* pflPercent, bool* pbAchieved);
		virtual int GetNextMostAchievedAchievementInfo(int iIteratorPrevious, char* pchName, std::uint32_t unNameBufLen, float* pflPercent, bool* pbAchieved);
		virtual bool GetAchievementAchievedPercent(const char* pchName, float* pflPercent);
		virtual std::uint64_t RequestGlobalStats(int nHistoryDays);
		virtual bool GetGlobalStat(const char* pchStatName, std::int64_t* pData);
		virtual bool GetGlobalStat(const char* pchStatName, double* pData);
		virtual int GetGlobalStatHistory(const char* pchStatName, std::int64_t* pData, std::uint32_t cubData);
		virtual int GetGlobalStatHistory(const char* pchStatName, double* pData, std::uint32_t cubData);
	};
}
