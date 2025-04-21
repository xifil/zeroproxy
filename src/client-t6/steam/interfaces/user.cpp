#include "common.hpp"
#include "steam/steam.hpp"

//#include "component/auth.hpp"

namespace steam {
	namespace {
		std::string auth_ticket;

		steam_id generate_steam_id() {
			steam_id id{};
			//id.bits = auth::get_guid();
			id.bits = 76561199152885728;
			return id;
		}
	}

	int user::GetHSteamUser() {
		return 1;
	}

	bool user::BLoggedOn() {
		return true;
	}

	steam_id user::GetSteamID() {
		static auto id = generate_steam_id();
		return id;
	}

	int user::InitiateGameConnection(void* pAuthBlob, int cbMaxAuthBlob, steam_id steamIDGameServer, unsigned int unIPServer, unsigned short usPortServer, bool bSecure) {
		return 0;
	}

	void user::TerminateGameConnection(unsigned int unIPServer, unsigned short usPortServer) {}

	void user::TrackAppUsageEvent(game_id gameID, int eAppUsageEvent, const char* pchExtraInfo) {
	}

	bool user::GetUserDataFolder(char* pchBuffer, int cubBuffer) {
		return false;
	}

	void user::StartVoiceRecording() {}

	void user::StopVoiceRecording() {}

	int user::GetAvailableVoice(unsigned int* pcbCompressed, unsigned int* pcbUncompressed, unsigned int nUncompressedVoiceDesiredSampleRate) {
		return 0;
	}

	int user::GetVoice(bool bWantCompressed, void* pDestBuffer, unsigned int cbDestBufferSize, unsigned int* nBytesWritten, bool bWantUncompressed, void* pUncompressedDestBuffer, unsigned int cbUncompressedDestBufferSize, unsigned int* nUncompressBytesWritten, unsigned int nUncompressedVoiceDesiredSampleRate) {
		return 2;
	}

	int user::DecompressVoice(const void* pCompressed, std::uint32_t cbCompressed, void* pDestBuffer, std::uint32_t cbDestBufferSize, std::uint32_t* nBytesWritten, std::uint32_t nDesiredSampleRate) {
		return 0;
	}

	unsigned int user::GetVoiceOptimalSampleRate() {
		return 0;
	}

	unsigned int user::GetAuthSessionTicket(void* pTicket, int cbMaxTicket, unsigned int* pcbTicket) {
		static uint32_t ticket = 0;
		*pcbTicket = 1;

		const auto result = callbacks::register_call();
		auto* response = static_cast<get_auth_session_ticket_response*>(calloc(1, sizeof(get_auth_session_ticket_response)));
		response->auth_ticket_ = ++ticket;
		response->result_ = 1; // k_EResultOK;

		callbacks::return_call(response, sizeof(get_auth_session_ticket_response), get_auth_session_ticket_response::callback_id, result);
		return response->auth_ticket_;
	}

	int user::BeginAuthSession(const void* pAuthTicket, int cbAuthTicket, steam_id steamID) {
		return 0;
	}

	void user::EndAuthSession(steam_id steamID) {}

	void user::CancelAuthTicket(unsigned int hAuthTicket) {}

	unsigned int user::UserHasLicenseForApp(steam_id steamID, unsigned int appID) {
		return 1;
	}

	bool user::BIsBehindNAT() {
		return false;
	}

	void user::AdvertiseGame(steam_id steamIDGameServer, unsigned int unIPServer, unsigned short usPortServer) {}

	unsigned long long user::RequestEncryptedAppTicket(void* pUserData, int cbUserData) {
		const auto id = this->GetSteamID();

		auth_ticket = "t6m";
		auth_ticket.resize(32);
		auth_ticket.append(static_cast<char*>(pUserData), 24);							// key
		auth_ticket.append(reinterpret_cast<const char*>(&id.bits), sizeof(id.bits));	// user id
		auth_ticket.append(&static_cast<char*>(pUserData)[24], 64);						// user name

		// Create the call response
		const auto result = callbacks::register_call();
		const auto retvals = static_cast<encrypted_app_ticket_response*>(calloc(1, sizeof(encrypted_app_ticket_response)));
		//::Utils::Memory::AllocateArray<EncryptedAppTicketResponse>();
		retvals->result_ = 1;

		// Return the call response
		callbacks::return_call(retvals, sizeof(encrypted_app_ticket_response), encrypted_app_ticket_response::callback_id, result);

		return result;
	}

	bool user::GetEncryptedAppTicket(void* pTicket, int cbMaxTicket, unsigned int* pcbTicket) {
		if (cbMaxTicket < 0 || auth_ticket.empty()) {
			return false;
		}

		const auto size = auth_ticket.size();
		if (static_cast<size_t>(cbMaxTicket) < size) {
			*pcbTicket = static_cast<unsigned>(size);
			return false;
		}

		std::memcpy(pTicket, auth_ticket.data(), size);
		*pcbTicket = static_cast<unsigned>(size);

		return true;
	}
}