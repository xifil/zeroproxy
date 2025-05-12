#include "common.hpp"
#include "steam/steam.hpp"

namespace steam {
	std::uint64_t screenshots::WriteScreenshot(void* pubRGB, std::uint32_t cubRGB, int nWidth, int nHeight) {
		return 0;
	}

	std::uint64_t screenshots::AddScreenshotToLibrary(const char* pchFilename, const char* pchThumbnailFilename, int nWidth, int nHeight) {
		return 0;
	}

	void screenshots::TriggerScreenshot() {}

	void screenshots::HookScreenshots(bool bHook) {}

	bool screenshots::SetLocation(std::uint64_t hScreenshot, const char* pchLocation) {
		return false;
	}

	bool screenshots::TagUser(std::uint64_t hScreenshot, steam_id steamID) {
		return false;
	}

	bool screenshots::TagPublishedFile(std::uint64_t hScreenshot, std::uint64_t unPublishedFileID) {
		return false;
	}
}
