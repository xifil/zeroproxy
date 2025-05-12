#include "common.hpp"
#include "steam/steam.hpp"

namespace steam {
	HTTPRequestHandle http::CreateHTTPRequest(std::uint32_t eHTTPRequestMethod, const char* pchAbsoluteURL) {
		return 0;
	}

	bool http::SetHTTPRequestContextValue(HTTPRequestHandle hRequest, std::uint64_t ulContextValue) {
		return false;
	}

	bool http::SetHTTPRequestNetworkActivityTimeout(HTTPRequestHandle hRequest, std::uint32_t unTimeoutSeconds) {
		return false;
	}

	bool http::SetHTTPRequestHeaderValue(HTTPRequestHandle hRequest, const char* pchHeaderName, const char* pchHeaderValue) {
		return false;
	}

	bool http::SetHTTPRequestGetOrPostParameter(HTTPRequestHandle hRequest, const char* pchParamName, const char* pchParamValue) {
		return false;
	}

	bool http::SendHTTPRequest(HTTPRequestHandle hRequest, std::uint64_t* pCallHandle) {
		return false;
	}

	bool http::DeferHTTPRequest(HTTPRequestHandle hRequest) {
		return false;
	}

	bool http::PrioritizeHTTPRequest(HTTPRequestHandle hRequest) {
		return false;
	}

	bool http::GetHTTPResponseHeaderSize(HTTPRequestHandle hRequest, const char* pchHeaderName, std::uint32_t* unResponseHeaderSize) {
		return false;
	}

	bool http::GetHTTPResponseHeaderValue(HTTPRequestHandle hRequest, const char* pchHeaderName, std::uint8_t* pHeaderValueBuffer, std::uint32_t unBufferSize) {
		return false;
	}

	bool http::GetHTTPResponseBodySize(HTTPRequestHandle hRequest, std::uint32_t* unBodySize) {
		return false;
	}

	bool http::GetHTTPResponseBodyData(HTTPRequestHandle hRequest, std::uint8_t* pBodyDataBuffer, std::uint32_t unBufferSize) {
		return false;
	}

	bool http::ReleaseHTTPRequest(HTTPRequestHandle hRequest) {
		return false;
	}

	bool http::GetHTTPDownloadProgressPct(HTTPRequestHandle hRequest, float* pflPercentOut) {
		return false;
	}

	bool http::SetHTTPRequestRawPostBody(HTTPRequestHandle hRequest, const char* pchContentType, std::uint8_t* pubBody, std::uint32_t unBodyLen) {
		return false;
	}
}
