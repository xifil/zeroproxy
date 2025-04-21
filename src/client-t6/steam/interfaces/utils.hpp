#pragma once

namespace steam {
	class utils {
	public:
		~utils() = default;

		virtual std::uint32_t GetSecondsSinceAppActive();
		virtual std::uint32_t GetSecondsSinceComputerActive();
		virtual int GetConnectedUniverse();
		virtual std::uint32_t GetServerRealTime();
		virtual const char* GetIPCountry();
		virtual bool GetImageSize(int iImage, std::uint32_t* pnWidth, std::uint32_t* pnHeight);
		virtual bool GetImageRGBA(int iImage, std::uint8_t* pubDest, int nDestBufferSize);
		virtual bool GetCSERIPPort(std::uint32_t* unIP, std::uint16_t* usPort);
		virtual std::uint8_t GetCurrentBatteryPower();
		virtual std::uint32_t GetAppID();
		virtual void SetOverlayNotificationPosition(int eNotificationPosition);
		virtual bool IsAPICallCompleted(std::uint64_t hSteamAPICall, bool* pbFailed);
		virtual int GetAPICallFailureReason(std::uint64_t hSteamAPICall);
		virtual bool GetAPICallResult(std::uint64_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool* pbFailed);
		virtual void RunFrame();
		virtual std::uint32_t GetIPCCallCount();
		virtual void SetWarningMessageHook(void (*pFunction)(int hpipe, const char* message));
		virtual bool IsOverlayEnabled();
		virtual bool BOverlayNeedsPresent();
		virtual std::uint64_t CheckFileSignature(const char* szFileName);
		virtual bool ShowGamepadTextInput(int eInputMode, int eInputLineMode, const char* szText, std::uint32_t uMaxLength);
		virtual std::uint32_t GetEnteredGamepadTextLength();
		virtual bool GetEnteredGamepadTextInput(char* pchValue, std::uint32_t cchValueMax);
	};
}
