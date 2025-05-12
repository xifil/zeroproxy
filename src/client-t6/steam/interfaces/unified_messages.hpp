#pragma once

namespace steam {
	using ClientUnifiedMessageHandle = std::uint64_t;

	class unified_messages {
	public:
		~unified_messages() = default;

		virtual ClientUnifiedMessageHandle SendMethod(const char* pchServiceMethod, const void* pRequestBuffer, std::uint32_t unRequestBufferSize,
			std::uint64_t unContext);
		virtual bool GetMethodResponseInfo(ClientUnifiedMessageHandle hHandle, std::uint32_t* punResponseSize, std::uint32_t* peResult);
		virtual bool GetMethodResponseData(ClientUnifiedMessageHandle hHandle, void* pResponseBuffer, std::uint32_t unResponseBufferSize, bool bAutoRelease);
		virtual bool ReleaseMethod(ClientUnifiedMessageHandle hHandle);
		virtual bool SendNotification(const char* pchServiceNotification, const void* pNotificationBuffer, std::uint32_t unNotificationBufferSize);
	};
}