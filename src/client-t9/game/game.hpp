#pragma once
#include "common.hpp"
#include "game/function_types.hpp"

namespace game {
	void init();

	bool is_server();

	// Functions
	inline functions::BB_AlertT* BB_Alert{};
	inline functions::CL_DisconnectT* CL_Disconnect{};
	inline functions::CL_DrawTextPhysicalT* CL_DrawTextPhysical{};
	inline functions::Com_SessionMode_SetNetworkModeT* Com_SessionMode_SetNetworkMode{};
	inline functions::Dvar_FindVarT* Dvar_FindVar{};
	inline functions::Dvar_ResetT* Dvar_Reset{};
	inline functions::Dvar_SetBoolFromSourceT* Dvar_SetBoolFromSource{};
	inline functions::Dvar_SetIntFromSourceT* Dvar_SetIntFromSource{};
	inline functions::LiveUser_GetUserDataForControllerT* LiveUser_GetUserDataForController{};
	inline functions::LobbyBase_SetNetworkModeT* LobbyBase_SetNetworkMode{};
	inline functions::unk_SetScreenT* unk_SetScreen{};
	inline functions::unk_SetUsernameT* unk_SetUsername{};

	// Fields
	inline t9::dvar_t** Dvar_ShowOverStack{};
	inline bool* Scr_Initialized{};
	inline t9::content_manager** unk_ContentManager{};
	inline char* unk_Config_1{};
	inline char* unk_Config_2{};
	inline t9::Font_s** unk_WatermarkFont{};

	// Other
	namespace exception {
		inline void* Dvar_GetBool{};
	}

	// Custom
	void set_mode(int mode, int menu);
}
