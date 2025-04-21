#include "common.hpp"
#include "steam/steam.hpp"

namespace steam {
	bool networking::SendP2PPacket(steam_id steamIDRemote, const void* pubData, std::uint32_t cubData, int eP2PSendType) {
		return false;
	}

	bool networking::IsP2PPacketAvailable(std::uint32_t* pcubMsgSize, int idk) {
		return false;
	}

	bool networking::ReadP2PPacket(void* pubDest, std::uint32_t cubDest, std::uint32_t* pcubMsgSize, steam_id* psteamIDRemote) {
		return false;
	}

	bool networking::AcceptP2PSessionWithUser(steam_id steamIDRemote) {
		return false;
	}

	bool networking::CloseP2PSessionWithUser(steam_id steamIDRemote) {
		return false;
	}

	bool networking::CloseP2PChannelWithUser(steam_id steamIDRemote, int iVirtualPort) {
		return false;
	}

	bool networking::GetP2PSessionState(steam_id steamIDRemote, void* pConnectionState) {
		return false;
	}

	bool networking::AllowP2PPacketRelay(bool bAllow) {
		return false;
	}

	std::uint32_t networking::CreateListenSocket(int nVirtualP2PPort, std::uint32_t nIP, std::uint16_t nPort, bool bAllowUseOfPacketRelay) {
		return NULL;
	}

	std::uint32_t networking::CreateP2PConnectionSocket(steam_id steamIDTarget, int nVirtualPort, int nTimeoutSec, bool bAllowUseOfPacketRelay) {
		return NULL;
	}

	std::uint32_t networking::CreateConnectionSocket(std::uint32_t nIP, std::uint16_t nPort, int nTimeoutSec) {
		return NULL;
	}

	bool networking::DestroySocket(std::uint32_t hSocket, bool bNotifyRemoteEnd) {
		return false;
	}

	bool networking::DestroyListenSocket(std::uint32_t hSocket, bool bNotifyRemoteEnd) {
		return false;
	}

	bool networking::SendDataOnSocket(std::uint32_t hSocket, void* pubData, std::uint32_t cubData, bool bReliable) {
		return false;
	}

	bool networking::IsDataAvailableOnSocket(std::uint32_t hSocket, std::uint32_t* pcubMsgSize) {
		return false;
	}

	bool networking::RetrieveDataFromSocket(std::uint32_t hSocket, void* pubDest, std::uint32_t cubDest, std::uint32_t* pcubMsgSize) {
		return false;
	}

	bool networking::IsDataAvailable(std::uint32_t hListenSocket, std::uint32_t* pcubMsgSize, std::uint32_t* phSocket) {
		return false;
	}

	bool networking::RetrieveData(std::uint32_t hListenSocket, void* pubDest, std::uint32_t cubDest, std::uint32_t* pcubMsgSize, std::uint32_t* phSocket) {
		return false;
	}

	bool networking::GetSocketInfo(std::uint32_t hSocket, steam_id* pSteamIDRemote, int* peSocketStatus, std::uint32_t* punIPRemote, std::uint16_t* punPortRemote) {
		return false;
	}

	bool networking::GetListenSocketInfo(std::uint32_t hListenSocket, std::uint32_t* pnIP, std::uint16_t* pnPort) {
		return false;
	}

	int networking::GetSocketConnectionType(std::uint32_t hSocket) {
		return 0;
	}

	int networking::GetMaxPacketSize(std::uint32_t hSocket) {
		return 0;
	}
}
