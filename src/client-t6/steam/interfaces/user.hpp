#pragma once

namespace steam {
	struct encrypted_app_ticket_response final {
		enum {
			callback_id = 154
		};

		int result_;
	};

	struct get_auth_session_ticket_response {
		enum {
			callback_id = 163
		};

		std::uint32_t auth_ticket_;
		int result_;
	};
	
	class user {
	public:
		~user() = default;

		virtual HSteamUser GetHSteamUser();
		virtual bool BLoggedOn();
		virtual steam_id GetSteamID();
		virtual int InitiateGameConnection(void* pAuthBlob, int cbMaxAuthBlob, steam_id steamIDGameServer, std::uint32_t unIPServer, std::uint16_t usPortServer, bool bSecure);
		virtual void TerminateGameConnection(std::uint32_t unIPServer, std::uint16_t usPortServer);
		virtual void TrackAppUsageEvent(game_id gameID, int eAppUsageEvent, const char* pchExtraInfo = "");
		virtual bool GetUserDataFolder(char* pchBuffer, int cubBuffer);
		virtual void StartVoiceRecording();
		virtual void StopVoiceRecording();
		virtual int GetAvailableVoice(std::uint32_t* pcbCompressed, std::uint32_t* pcbUncompressed, std::uint32_t nUncompressedVoiceDesiredSampleRate);
		virtual int GetVoice(bool bWantCompressed, void* pDestBuffer, std::uint32_t cbDestBufferSize, std::uint32_t* nBytesWritten, bool bWantUncompressed, void* pUncompressedDestBuffer, std::uint32_t cbUncompressedDestBufferSize, std::uint32_t* nUncompressBytesWritten, std::uint32_t nUncompressedVoiceDesiredSampleRate);
		virtual int DecompressVoice(const void* pCompressed, std::uint32_t cbCompressed, void* pDestBuffer, std::uint32_t cbDestBufferSize, std::uint32_t* nBytesWritten, std::uint32_t nDesiredSampleRate);
		virtual std::uint32_t GetVoiceOptimalSampleRate();
		virtual std::uint32_t GetAuthSessionTicket(void* pTicket, int cbMaxTicket, std::uint32_t* pcbTicket);
		virtual int BeginAuthSession(const void* pAuthTicket, int cbAuthTicket, steam_id steamID);
		virtual void EndAuthSession(steam_id steamID);
		virtual void CancelAuthTicket(std::uint32_t hAuthTicket);
		virtual std::uint32_t UserHasLicenseForApp(steam_id steamID, std::uint32_t appID);
		virtual bool BIsBehindNAT();
		virtual void AdvertiseGame(steam_id steamIDGameServer, std::uint32_t unIPServer, std::uint16_t usPortServer);
		virtual std::uint64_t RequestEncryptedAppTicket(void* pDataToInclude, int cbDataToInclude);
		virtual bool GetEncryptedAppTicket(void* pTicket, int cbMaxTicket, std::uint32_t* pcbTicket);
	};
}
