#include "common.hpp"
#include "steam/steam.hpp"

namespace steam {
	bool content_server::LogOn(std::uint32_t uContentServerID) {
		return true;
	}
	
	bool content_server::LogOff() {
		return true;
	}
	
	bool content_server::BLoggedOn() {
		return true;
	}
	
	void content_server::SendClientContentAuthRequest(steam_id steamID, std::uint32_t uContentID, std::uint64_t ulSessionToken, bool bTokenPresent) {}
	
	bool content_server::BCheckTicket(steam_id steamID, std::uint32_t uContentID, const void* pvTicketData, std::uint32_t cubTicketLength) {
		return true;
	}
}
