#pragma once
#include "common.hpp"
#include "game/function_types.hpp"

namespace game {
	void init();

	inline functions::Com_PrintMessageT* Com_PrintMessage{};
	inline functions::Content_DoWeHaveContentPackT* Content_DoWeHaveContentPack{};
	inline functions::Content_GetAvailableContentPacksT* Content_GetAvailableContentPacks{};
	inline functions::Content_HasEntitlementOwnershipByRefT* Content_HasEntitlementOwnershipByRef{};
	inline functions::FS_FindXZoneT* FS_FindXZone{};
	inline functions::MSStore_OwnsContentT* MSStore_OwnsContent{};
	inline functions::unk_GenericACFunctionT* unk_AC_OnDllLoaded{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk2_Threaded{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk3{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk4{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk5{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk6{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk7{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk8{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk10{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk11{};
	inline functions::unk_GenericACFunctionT* unk_AC_Unk13_Threaded{};

	inline int* s_contentPackMetaData{};
	inline std::uint64_t* unk_AC_State{};
	inline std::uint8_t* unk_OwnedContent{};

	bool is_server();
}
