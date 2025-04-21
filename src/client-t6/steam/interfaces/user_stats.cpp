#include "common.hpp"
#include "steam/steam.hpp"

namespace steam {
	namespace {
		struct user_stats_received {
			enum {
				callback_id = 1101
			};

			uint64_t game_id_;
			int result_;
			steam_id steam_id_user_;
		};
	}

	bool user_stats::RequestCurrentStats() {
		game_id game;
		game.raw.mod_id = 0;
		game.raw.type = 0;
		game.raw.app_id = SteamUtils()->GetAppID();

		const auto result = callbacks::register_call();
		auto* response = static_cast<user_stats_received*>(calloc(1, sizeof(user_stats_received)));
		response->steam_id_user_ = SteamUser()->GetSteamID();
		response->result_ = 1; // k_EResultOK;
		response->game_id_ = game.bits;

		callbacks::return_call(response, sizeof(user_stats_received), user_stats_received::callback_id, result);
		return true;
	}

	bool user_stats::GetStat(const char* pchName, int* pData) {
		return false;
	}

	bool user_stats::GetStat(const char* pchName, float* pData) {
		return false;
	}

	bool user_stats::SetStat(const char* pchName, int nData) {
		return true;
	}

	bool user_stats::SetStat(const char* pchName, float fData) {
		return true;
	}

	bool user_stats::UpdateAvgRateStat(const char* pchName, float flCountThisSession, double dSessionLength) {
		return false;
	}

	bool user_stats::GetAchievement(const char* pchName, bool* pbAchieved) {
		return true;
	}

	bool user_stats::SetAchievement(const char* pchName) {
		return true;
	}

	bool user_stats::ClearAchievement(const char* pchName) {
		return true;
	}

	bool user_stats::GetAchievementAndUnlockTime(const char* pchName, bool* pbAchieved, std::uint32_t* punUnlockTime) {
		return true;
	}

	bool user_stats::StoreStats() {
		return true;
	}

	int user_stats::GetAchievementIcon(const char* pchName) {
		return 0;
	}

	const char* user_stats::GetAchievementDisplayAttribute(const char* pchName, const char* pchKey) {
		return "";
	}

	bool user_stats::IndicateAchievementProgress(const char* pchName, std::uint32_t nCurProgress, std::uint32_t nMaxProgress) {
		return true;
	}

	std::uint32_t user_stats::GetNumAchievements(game_id nGameID) {
		return 0;
	}

	const char* user_stats::GetAchievementName(std::uint32_t iAchievement) {
		return "";
	}

	std::uint64_t user_stats::RequestUserStats(steam_id steamIDUser) {
		return 0;
	}

	bool user_stats::GetUserStat(steam_id steamIDUser, const char* pchName, int* pData) {
		return false;
	}

	bool user_stats::GetUserStat(steam_id steamIDUser, const char* pchName, float* pData) {
		return false;
	}

	bool user_stats::GetUserAchievement(steam_id steamIDUser, const char* pchName, bool* pbAchieved) {
		return true;
	}

	bool user_stats::GetUserAchievementAndUnlockTime(steam_id steamIDUser, const char* pchName, bool* pbAchieved, std::uint32_t* punUnlockTime) {
		return true;
	}

	bool user_stats::ResetAllStats(bool bAchievementsToo) {
		return false;
	}

	std::uint64_t user_stats::FindOrCreateLeaderboard(const char* pchLeaderboardName, int eLeaderboardSortMethod, int eLeaderboardDisplayType) {
		return 0;
	}

	std::uint64_t user_stats::FindLeaderboard(const char* pchLeaderboardName) {
		return 0;
	}

	const char* user_stats::GetLeaderboardName(std::uint64_t hSteamLeaderboard) {
		return "";
	}

	int user_stats::GetLeaderboardEntryCount(std::uint64_t hSteamLeaderboard) {
		return 0;
	}

	int user_stats::GetLeaderboardSortMethod(std::uint64_t hSteamLeaderboard) {
		return 0;
	}

	int user_stats::GetLeaderboardDisplayType(std::uint64_t hSteamLeaderboard) {
		return 0;
	}

	std::uint64_t user_stats::DownloadLeaderboardEntries(std::uint64_t hSteamLeaderboard, int eLeaderboardDataRequest, int nRangeStart, int nRangeEnd) {
		return 0;
	}

	std::uint64_t user_stats::DownloadLeaderboardEntriesForUsers(std::uint64_t hSteamLeaderboard, steam_id* prgUsers, int cUsers) {
		return 0;
	}

	bool user_stats::GetDownloadedLeaderboardEntry(std::uint64_t hSteamLeaderboardEntries, int index, int* pLeaderboardEntry, int* pDetails, int cDetailsMax) {
		return false;
	}

	std::uint64_t user_stats::UploadLeaderboardScore(std::uint64_t hSteamLeaderboard, int eLeaderboardUploadScoreMethod, int nScore,
		const int* pScoreDetails, int cScoreDetailsCount)
	{
		return 0;
	}

	std::uint64_t user_stats::AttachLeaderboardUGC(std::uint64_t hSteamLeaderboard, std::uint64_t hUGC) {
		return 0;
	}

	std::uint64_t user_stats::GetNumberOfCurrentPlayers() {
		return 0;
	}

	std::uint64_t user_stats::RequestGlobalAchievementPercentages() {
		return 0;
	}

	int user_stats::GetMostAchievedAchievementInfo(char* pchName, std::uint32_t unNameBufLen, float* pflPercent, bool* pbAchieved) {
		return 0;
	}

	int user_stats::GetNextMostAchievedAchievementInfo(int iIteratorPrevious, char* pchName, std::uint32_t unNameBufLen, float* pflPercent, bool* pbAchieved) {
		return 0;
	}

	bool user_stats::GetAchievementAchievedPercent(const char* pchName, float* pflPercent) {
		return true;
	}

	std::uint64_t user_stats::RequestGlobalStats(int nHistoryDays) {
		return 0;
	}

	bool user_stats::GetGlobalStat(const char* pchStatName, std::int64_t* pData) {
		return false;
	}

	bool user_stats::GetGlobalStat(const char* pchStatName, double* pData) {
		return false;
	}

	int user_stats::GetGlobalStatHistory(const char* pchStatName, std::int64_t* pData, std::uint32_t cubData) {
		return 0;
	}

	int user_stats::GetGlobalStatHistory(const char* pchStatName, double* pData, std::uint32_t cubData) {
		return 0;
	}
}
