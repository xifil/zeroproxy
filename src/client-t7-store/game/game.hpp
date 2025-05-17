#pragma once
#include "common.hpp"
#include "game/function_types.hpp"

namespace game {
	void init();

	inline functions::Com_PrintMessageT* Com_PrintMessage{};
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

	inline std::uint64_t* unk_AC_State{};

	bool is_server();
}
