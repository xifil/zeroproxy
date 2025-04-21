#include "common.hpp"
#include "steam/steam.hpp"

namespace steam {
	bool apps::BIsSubscribed() {
		return true;
	}

	bool apps::BIsLowViolence() {
		return false;
	}

	bool apps::BIsCybercafe() {
		return false;
	}

	bool apps::BIsVACBanned() {
		return false;
	}

	const char* apps::GetCurrentGameLanguage() {
		return "english";
	}

	const char* apps::GetAvailableGameLanguages() {
		return "english";
	}

	bool apps::BIsSubscribedApp(std::uint32_t nAppID) {
		return true;
	}

	bool apps::BIsDlcInstalled(std::uint32_t nAppID) {
		return true;
	}

	std::uint32_t apps::GetEarliestPurchaseUnixTime(std::uint32_t nAppID) {
		return 0;
	}

	bool apps::BIsSubscribedFromFreeWeekend() {
		return false;
	}

	int apps::GetDLCCount() {
		return 0;
	}

	bool apps::BGetDLCDataByIndex(int iDLC, std::uint32_t* pAppID, bool* pbAvailable, char* pchName, int cchNameBufferSize) {
		return false;
	}

	void apps::InstallDLC(std::uint32_t nAppID) {}

	void apps::UninstallDLC(std::uint32_t nAppID) {}

	void apps::RequestAppProofOfPurchaseKey(std::uint32_t nAppID) {}

	bool apps::GetCurrentBetaName(char* pchName, int cchNameBufferSize) {
		strncpy_s(pchName, cchNameBufferSize, "public", cchNameBufferSize);
		return true;
	}

	bool apps::MarkContentCorrupt(bool bMissingFilesOnly) {
		return false;
	}

	std::uint32_t apps::GetInstalledDepots(std::uint32_t* pvecDepots, std::uint32_t cMaxDepots) {
		return 0;
	}

	std::uint32_t apps::GetAppInstallDir(std::uint32_t appID, char* pchFolder, std::uint32_t cchFolderBufferSize) {
		return 0;
	}

	bool apps::BIsAppInstalled(std::uint32_t appID) {
		return false;
	}
}
