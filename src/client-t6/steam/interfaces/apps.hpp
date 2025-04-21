#pragma once

namespace steam {
	class apps {
	public:
		~apps() = default;
		
		virtual bool BIsSubscribed();
		virtual bool BIsLowViolence();
		virtual bool BIsCybercafe();
		virtual bool BIsVACBanned();
		virtual const char* GetCurrentGameLanguage();
		virtual const char* GetAvailableGameLanguages();
		virtual bool BIsSubscribedApp(std::uint32_t nAppID);
		virtual bool BIsDlcInstalled(std::uint32_t nAppID);
		virtual std::uint32_t GetEarliestPurchaseUnixTime(std::uint32_t nAppID);
		virtual bool BIsSubscribedFromFreeWeekend();
		virtual int GetDLCCount();
		virtual bool BGetDLCDataByIndex(int iDLC, std::uint32_t* pAppID, bool* pbAvailable, char* pchName, int cchNameBufferSize);
		virtual void InstallDLC(std::uint32_t nAppID);
		virtual void UninstallDLC(std::uint32_t nAppID);
		virtual void RequestAppProofOfPurchaseKey(std::uint32_t nAppID);
		virtual bool GetCurrentBetaName(char* pchName, int cchNameBufferSize);
		virtual bool MarkContentCorrupt(bool bMissingFilesOnly);
		virtual std::uint32_t GetInstalledDepots(std::uint32_t* pvecDepots, std::uint32_t cMaxDepots);
		virtual std::uint32_t GetAppInstallDir(std::uint32_t appID, char* pchFolder, std::uint32_t cchFolderBufferSize);
		virtual bool BIsAppInstalled(std::uint32_t appID);
	};
}