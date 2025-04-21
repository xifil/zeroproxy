#pragma once

namespace steam {
	using HTTPRequestHandle = uint64_t;
	using HTTPCookieContainerHandle = uint64_t;
	
	class http {
	public:
		~http() = default;

		virtual HTTPRequestHandle CreateHTTPRequest(std::uint32_t eHTTPRequestMethod, const char* pchAbsoluteURL);
		virtual bool SetHTTPRequestContextValue(HTTPRequestHandle hRequest, std::uint64_t ulContextValue);
		virtual bool SetHTTPRequestNetworkActivityTimeout(HTTPRequestHandle hRequest, std::uint32_t unTimeoutSeconds);
		virtual bool SetHTTPRequestHeaderValue(HTTPRequestHandle hRequest, const char* pchHeaderName, const char* pchHeaderValue);
		virtual bool SetHTTPRequestGetOrPostParameter(HTTPRequestHandle hRequest, const char* pchParamName, const char* pchParamValue);
		virtual bool SendHTTPRequest(HTTPRequestHandle hRequest, std::uint64_t* pCallHandle);
		virtual bool DeferHTTPRequest(HTTPRequestHandle hRequest);
		virtual bool PrioritizeHTTPRequest(HTTPRequestHandle hRequest);
		virtual bool GetHTTPResponseHeaderSize(HTTPRequestHandle hRequest, const char* pchHeaderName, std::uint32_t* unResponseHeaderSize);
		virtual bool GetHTTPResponseHeaderValue(HTTPRequestHandle hRequest, const char* pchHeaderName, std::uint8_t* pHeaderValueBuffer, std::uint32_t unBufferSize);
		virtual bool GetHTTPResponseBodySize(HTTPRequestHandle hRequest, std::uint32_t* unBodySize);
		virtual bool GetHTTPResponseBodyData(HTTPRequestHandle hRequest, std::uint8_t* pBodyDataBuffer, std::uint32_t unBufferSize);
		virtual bool ReleaseHTTPRequest(HTTPRequestHandle hRequest);
		virtual bool GetHTTPDownloadProgressPct(HTTPRequestHandle hRequest, float* pflPercentOut);
		virtual bool SetHTTPRequestRawPostBody(HTTPRequestHandle hRequest, const char* pchContentType, std::uint8_t* pubBody, std::uint32_t unBodyLen);
	};
}
