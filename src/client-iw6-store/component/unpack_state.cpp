#include "common.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

namespace unpack_state {
	namespace {
		utils::hook::iat_detour system_parameters_info_a_hook;

		HANDLE system_parameters_info_a_stub(const UINT uiAction, const UINT uiParam, const PVOID pvParam, const UINT fWinIni) {
			component_loader::post_unpack();
			return system_parameters_info_a_hook.invoke<HANDLE>(uiAction, uiParam, pvParam, fWinIni);
		}
	}

	struct component final : generic_component {
		void post_load() override {
			system_parameters_info_a_hook.create({}, "user32.dll", "SystemParametersInfoA", system_parameters_info_a_stub);
		}
	};
}

REGISTER_COMPONENT(unpack_state::component)