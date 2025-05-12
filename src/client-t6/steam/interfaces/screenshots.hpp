#pragma once

namespace steam {
	class screenshots {
	public:
		~screenshots() = default;

		virtual std::uint64_t WriteScreenshot(void* pubRGB, std::uint32_t cubRGB, int nWidth, int nHeight);
		virtual std::uint64_t AddScreenshotToLibrary(const char* pchFilename, const char* pchThumbnailFilename, int nWidth, int nHeight);
		virtual void TriggerScreenshot();
		virtual void HookScreenshots(bool bHook);
		virtual bool SetLocation(std::uint64_t hScreenshot, const char* pchLocation);
		virtual bool TagUser(std::uint64_t hScreenshot, steam_id steamID);
		virtual bool TagPublishedFile(std::uint64_t hScreenshot, std::uint64_t unPublishedFileID);
	};
}