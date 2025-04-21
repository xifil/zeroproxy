#include "common.hpp"
#include "steam/steam.hpp"

namespace steam {
	bool remote_storage::FileWrite(const char* pchFile, const void* pvData, int cubData) {
		return true;
	}

	int remote_storage::FileRead(const char* pchFile, void* pvData, int cubDataToRead) {
		return 0;
	}

	bool remote_storage::FileForget(const char* pchFile) {
		return true;
	}

	bool remote_storage::FileDelete(const char* pchFile) {
		return true;
	}

	std::uint64_t remote_storage::FileShare(const char* pchFile) {
		return 0;
	}

	bool remote_storage::SetSyncPlatforms(const char* pchFile, std::uint32_t eRemoteStoragePlatform) {
		return true;
	}

	std::uint64_t remote_storage::FileWriteStreamOpen(const char* pchFile) {
		return 0;
	}

	int remote_storage::FileWriteStreamWriteChunk(std::uint64_t hStream, const void* pvData, int cubData) {
		return 1;
	}

	int remote_storage::FileWriteStreamClose(std::uint64_t hStream) {
		return 1;
	}

	int remote_storage::FileWriteStreamCancel(std::uint64_t hStream) {
		return 1;
	}

	bool remote_storage::FileExists(const char* pchFile) {
		return true;
	}

	bool remote_storage::FilePersisted(const char* pchFile) {
		return true;
	}

	int remote_storage::GetFileSize(const char* pchFile) {
		return 0;
	}

	std::int64_t remote_storage::GetFileTimestamp(const char* pchFile) {
		return 0;
	}

	unsigned remote_storage::GetSyncPlatforms(const char* pchFile) {
		return 0;
	}

	int remote_storage::GetFileCount() {
		return 0;
	}

	const char* remote_storage::GetFileNameAndSize(int iFile, int* pnFileSizeInBytes) {
		*pnFileSizeInBytes = 0;
		return "";
	}

	bool remote_storage::GetQuota(int* pnTotalBytes, int* puAvailableBytes) {
		*pnTotalBytes = 0x10000000;
		*puAvailableBytes = 0x10000000;
		return false;
	}

	bool remote_storage::IsCloudEnabledForAccount() {
		return false;
	}

	bool remote_storage::IsCloudEnabledForApp() {
		return false;
	}

	void remote_storage::SetCloudEnabledForApp(bool bEnabled) {}

	std::uint64_t remote_storage::UGCDownload(std::uint64_t hContent, std::uint32_t uUnk) {
		return 0;
	}

	bool remote_storage::GetUGCDownloadProgress(std::uint64_t hContent, std::uint32_t* puDownloadedBytes, std::uint32_t* puTotalBytes) {
		return false;
	}

	bool remote_storage::GetUGCDetails(std::uint64_t hContent, std::uint32_t* pnAppID, char** ppchName, int* pnFileSizeInBytes, steam_id* pSteamIDOwner) {
		return false;
	}

	int remote_storage::UGCRead(std::uint64_t hContent, void* pvData, int cubDataToRead, std::uint32_t uOffset) {
		return 0;
	}

	int remote_storage::GetCachedUGCCount() {
		return 0;
	}

	std::uint64_t remote_storage::GetCachedUGCHandle(int iCachedContent) {
		return 0;
	}

	std::uint64_t remote_storage::PublishWorkshopFile(const char* pchFile, const char* pchPreviewFile, std::uint32_t nConsumerAppId, const char* pchTitle, const char* pchDescription, std::uint32_t eVisibility, int* pTags, std::uint32_t eWorkshopFileType) {
		return 0;
	}

	std::uint64_t remote_storage::CreatePublishedFileUpdateRequest(std::uint64_t unPublishedFileId) {
		return 0;
	}

	bool remote_storage::UpdatePublishedFileFile(std::uint64_t hUpdateRequest, const char* pchFile) {
		return false;
	}

	bool remote_storage::UpdatePublishedFilePreviewFile(std::uint64_t hUpdateRequest, const char* pchPreviewFile) {
		return false;
	}

	bool remote_storage::UpdatePublishedFileTitle(std::uint64_t hUpdateRequest, const char* pchTitle) {
		return false;
	}

	bool remote_storage::UpdatePublishedFileDescription(std::uint64_t hUpdateRequest, const char* pchDescription) {
		return false;
	}

	bool remote_storage::UpdatePublishedFileVisibility(std::uint64_t hUpdateRequest, std::uint32_t eVisibility) {
		return false;
	}

	bool remote_storage::UpdatePublishedFileTags(std::uint64_t hUpdateRequest, int* pTags) {
		return false;
	}

	std::uint64_t remote_storage::CommitPublishedFileUpdate(std::uint64_t hUpdateRequest) {
		return 0;
	}

	std::uint64_t remote_storage::GetPublishedFileDetails(std::uint64_t unPublishedFileId) {
		return 0;
	}

	std::uint64_t remote_storage::DeletePublishedFile(std::uint64_t unPublishedFileId) {
		return 0;
	}

	std::uint64_t remote_storage::EnumerateUserPublishedFiles(std::uint32_t uStartIndex) {
		return 0;
	}

	std::uint64_t remote_storage::SubscribePublishedFile(std::uint64_t unPublishedFileId) {
		return 0;
	}

	std::uint64_t remote_storage::EnumerateUserSubscribedFiles(std::uint32_t uStartIndex) {
		return 0;
	}

	std::uint64_t remote_storage::UnsubscribePublishedFile(std::uint64_t unPublishedFileId) {
		return 0;
	}

	bool remote_storage::UpdatePublishedFileSetChangeDescription(std::uint64_t hUpdateRequest, const char* cszDescription) {
		return false;
	}

	std::uint64_t remote_storage::GetPublishedItemVoteDetails(std::uint64_t unPublishedFileId) {
		return 0;
	}

	std::uint64_t remote_storage::UpdateUserPublishedItemVote(std::uint64_t unPublishedFileId, bool bVoteUp) {
		return 0;
	}

	std::uint64_t remote_storage::GetUserPublishedItemVoteDetails(std::uint64_t unPublishedFileId) {
		return 0;
	}

	std::uint64_t remote_storage::EnumerateUserSharedWorkshopFiles(std::uint32_t nAppId, steam_id creatorSteamID, std::uint32_t uStartIndex, int* pRequiredTags, int* pExcludedTags) {
		return 0;
	}

	std::uint64_t remote_storage::PublishVideo(std::uint32_t eVideoProvider, const char* cszVideoAccountName, const char* cszVideoIdentifier, const char* cszFileName, std::uint32_t nConsumerAppId, const char* cszTitle, const char* cszDescription, std::uint32_t eVisibility, int* pTags) {
		return 0;
	}

	std::uint64_t remote_storage::SetUserPublishedFileAction(std::uint64_t unPublishedFileId, std::uint32_t eAction) {
		return 0;
	}

	std::uint64_t remote_storage::EnumeratePublishedFilesByUserAction(std::uint32_t eAction, std::uint32_t uStartIndex) {
		return 0;
	}

	std::uint64_t remote_storage::EnumeratePublishedWorkshopFiles(std::uint32_t eType, std::uint32_t uStartIndex, std::uint32_t cDays, std::uint32_t cCount, int* pTags, int* pUserTags) {
		return 0;
	}
}
