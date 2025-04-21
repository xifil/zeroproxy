#pragma once

namespace steam {
	class content_server {
	public:
		~content_server() = default;
		
		virtual bool LogOn(std::uint32_t uContentServerID);
		virtual bool LogOff();
		virtual bool BLoggedOn();
		virtual void SendClientContentAuthRequest(steam_id steamID, std::uint32_t uContentID, std::uint64_t ulSessionToken, bool bTokenPresent);
		virtual bool BCheckTicket(steam_id steamID, std::uint32_t uContentID, const void* pvTicketData, std::uint32_t cubTicketLength);
	};
}
