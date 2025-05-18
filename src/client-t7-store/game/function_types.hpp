#pragma once
#include "common.hpp"

namespace functions {
	using Com_Frame_Try_Block_FunctionT = void();
	using Com_PrintMessageT = void(int channel, int console_type, const char* message, int unk);
	using Content_DoWeHaveContentPackT = bool();
	using Content_GetAvailableContentPacksT = std::uint64_t(char a1);
	using Content_HasEntitlementOwnershipByRefT = bool();
	using FS_FindXZoneT = const char*(const char* file_name);
	using MSStore_OwnsContentT = bool();
	using SND_EndFrameT = void();
	using unk_GenericACFunctionT = void();
	using unk_InitSysDvarsT = void();
	using unk_WaitForObjectsT = std::int64_t();
}
