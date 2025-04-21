#pragma once

namespace steam {
	class networking {
	public:
		~networking() = default;

		virtual bool SendP2PPacket(steam_id steamIDRemote, const void* pubData, std::uint32_t cubData, int eP2PSendType);
		virtual bool IsP2PPacketAvailable(std::uint32_t* pcubMsgSize, int idk);
		virtual bool ReadP2PPacket(void* pubDest, std::uint32_t cubDest, std::uint32_t* pcubMsgSize, steam_id* psteamIDRemote);
		virtual bool AcceptP2PSessionWithUser(steam_id steamIDRemote);
		virtual bool CloseP2PSessionWithUser(steam_id steamIDRemote);
		virtual bool CloseP2PChannelWithUser(steam_id steamIDRemote, int iVirtualPort);
		virtual bool GetP2PSessionState(steam_id steamIDRemote, void* pConnectionState);
		virtual bool AllowP2PPacketRelay(bool bAllow);
		virtual std::uint32_t CreateListenSocket(int nVirtualP2PPort, std::uint32_t nIP, std::uint16_t nPort, bool bAllowUseOfPacketRelay);
		virtual std::uint32_t CreateP2PConnectionSocket(steam_id steamIDTarget, int nVirtualPort, int nTimeoutSec, bool bAllowUseOfPacketRelay);
		virtual std::uint32_t CreateConnectionSocket(std::uint32_t nIP, std::uint16_t nPort, int nTimeoutSec);
		virtual bool DestroySocket(std::uint32_t hSocket, bool bNotifyRemoteEnd);
		virtual bool DestroyListenSocket(std::uint32_t hSocket, bool bNotifyRemoteEnd);
		virtual bool SendDataOnSocket(std::uint32_t hSocket, void* pubData, std::uint32_t cubData, bool bReliable);
		virtual bool IsDataAvailableOnSocket(std::uint32_t hSocket, std::uint32_t* pcubMsgSize);
		virtual bool RetrieveDataFromSocket(std::uint32_t hSocket, void* pubDest, std::uint32_t cubDest, std::uint32_t* pcubMsgSize);
		virtual bool IsDataAvailable(std::uint32_t hListenSocket, std::uint32_t* pcubMsgSize, std::uint32_t* phSocket);
		virtual bool RetrieveData(std::uint32_t hListenSocket, void* pubDest, std::uint32_t cubDest, std::uint32_t* pcubMsgSize, std::uint32_t* phSocket);
		virtual bool GetSocketInfo(std::uint32_t hSocket, steam_id* pSteamIDRemote, int* peSocketStatus, std::uint32_t* punIPRemote, std::uint16_t* punPortRemote);
		virtual bool GetListenSocketInfo(std::uint32_t hListenSocket, std::uint32_t* pnIP, std::uint16_t* pnPort);
		virtual int GetSocketConnectionType(std::uint32_t hSocket);
		virtual int GetMaxPacketSize(std::uint32_t hSocket);
	};
}
