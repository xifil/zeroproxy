#pragma once

namespace steam {
	class remote_storage {
	public:
		~remote_storage() = default;

		virtual bool FileWrite(const char* pchFile, const void* pvData, int cubData);
		virtual int FileRead(const char* pchFile, void* pvData, int cubDataToRead);
		virtual bool FileForget(const char* pchFile);
		virtual bool FileDelete(const char* pchFile);
		virtual std::uint64_t FileShare(const char* pchFile);
		virtual bool SetSyncPlatforms(const char* pchFile, std::uint32_t eRemoteStoragePlatform);
		virtual std::uint64_t FileWriteStreamOpen(const char* pchFile);
		virtual int FileWriteStreamWriteChunk(std::uint64_t hStream, const void* pvData, int cubData);
		virtual int FileWriteStreamClose(std::uint64_t hStream);
		virtual int FileWriteStreamCancel(std::uint64_t hStream);
		virtual bool FileExists(const char* pchFile);
		virtual bool FilePersisted(const char* pchFile);
		virtual int GetFileSize(const char* pchFile);
		virtual std::int64_t GetFileTimestamp(const char* pchFile);
		virtual std::uint32_t GetSyncPlatforms(const char* pchFile);
		virtual int GetFileCount();
		virtual const char* GetFileNameAndSize(int iFile, int* pnFileSizeInBytes);
		virtual bool GetQuota(int* pnTotalBytes, int* puAvailableBytes);
		virtual bool IsCloudEnabledForAccount();
		virtual bool IsCloudEnabledForApp();
		virtual void SetCloudEnabledForApp(bool bEnabled);
		virtual std::uint64_t UGCDownload(std::uint64_t hContent, std::uint32_t uUnk);
		virtual bool GetUGCDownloadProgress(std::uint64_t hContent, std::uint32_t* puDownloadedBytes, std::uint32_t* puTotalBytes);
		virtual bool GetUGCDetails(std::uint64_t hContent, std::uint32_t* pnAppID, char** ppchName, int* pnFileSizeInBytes, steam_id* pSteamIDOwner);
		virtual int UGCRead(std::uint64_t hContent, void* pvData, int cubDataToRead, std::uint32_t uOffset);
		virtual int GetCachedUGCCount();
		virtual std::uint64_t GetCachedUGCHandle(int iCachedContent);
		virtual std::uint64_t PublishWorkshopFile(const char* pchFile, const char* pchPreviewFile, std::uint32_t nConsumerAppId, const char* pchTitle, const char* pchDescription, std::uint32_t eVisibility, int* pTags, std::uint32_t eWorkshopFileType);
		virtual std::uint64_t CreatePublishedFileUpdateRequest(std::uint64_t unPublishedFileId);
		virtual bool UpdatePublishedFileFile(std::uint64_t hUpdateRequest, const char* pchFile);
		virtual bool UpdatePublishedFilePreviewFile(std::uint64_t hUpdateRequest, const char* pchPreviewFile);
		virtual bool UpdatePublishedFileTitle(std::uint64_t hUpdateRequest, const char* pchTitle);
		virtual bool UpdatePublishedFileDescription(std::uint64_t hUpdateRequest, const char* pchDescription);
		virtual bool UpdatePublishedFileVisibility(std::uint64_t hUpdateRequest, std::uint32_t eVisibility);
		virtual bool UpdatePublishedFileTags(std::uint64_t hUpdateRequest, int* pTags);
		virtual std::uint64_t CommitPublishedFileUpdate(std::uint64_t hUpdateRequest);
		virtual std::uint64_t GetPublishedFileDetails(std::uint64_t unPublishedFileId);
		virtual std::uint64_t DeletePublishedFile(std::uint64_t unPublishedFileId);
		virtual std::uint64_t EnumerateUserPublishedFiles(std::uint32_t uStartIndex);
		virtual std::uint64_t SubscribePublishedFile(std::uint64_t unPublishedFileId);
		virtual std::uint64_t EnumerateUserSubscribedFiles(std::uint32_t uStartIndex);
		virtual std::uint64_t UnsubscribePublishedFile(std::uint64_t unPublishedFileId);
		virtual bool UpdatePublishedFileSetChangeDescription(std::uint64_t hUpdateRequest, const char* cszDescription);
		virtual std::uint64_t GetPublishedItemVoteDetails(std::uint64_t unPublishedFileId);
		virtual std::uint64_t UpdateUserPublishedItemVote(std::uint64_t unPublishedFileId, bool bVoteUp);
		virtual std::uint64_t GetUserPublishedItemVoteDetails(std::uint64_t unPublishedFileId);
		virtual std::uint64_t EnumerateUserSharedWorkshopFiles(std::uint32_t nAppId, steam_id creatorSteamID, std::uint32_t uStartIndex, int* pRequiredTags, int* pExcludedTags);
		virtual std::uint64_t PublishVideo(std::uint32_t eVideoProvider, const char* cszVideoAccountName, const char* cszVideoIdentifier, const char* cszFileName, std::uint32_t nConsumerAppId, const char* cszTitle, const char* cszDescription, std::uint32_t eVisibility, int* pTags);
		virtual std::uint64_t SetUserPublishedFileAction(std::uint64_t unPublishedFileId, std::uint32_t eAction);
		virtual std::uint64_t EnumeratePublishedFilesByUserAction(std::uint32_t eAction, std::uint32_t uStartIndex);
		virtual std::uint64_t EnumeratePublishedWorkshopFiles(std::uint32_t eType, std::uint32_t uStartIndex, std::uint32_t cDays, std::uint32_t cCount, int* pTags, int* pUserTags);
	};
}
