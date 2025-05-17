#pragma once
#include "common.hpp"

namespace functions {
	using Com_PrintMessageT = void(int channel, int console_type, const char* message, int unk);
	using Content_DoWeHaveContentPackT = bool();
	using Content_GetAvailableContentPacksT = std::uint64_t(char a1);
	using Content_HasEntitlementOwnershipByRefT = bool();
	using FS_FindXZoneT = const char*(const char* file_name);
	using MSStore_OwnsContentT = bool();
	using unk_GenericACFunctionT = void();
}
