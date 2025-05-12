#include "common.hpp"
#include "steam/steam.hpp"

namespace steam {
	bool controller::Init() {
		return true;
	}

	bool controller::Shutdown() {
		return true;
	}

	void controller::RunFrame() {}

	int controller::GetConnectedControllers(ControllerHandle_t* handlesOut) {
		return 0;
	}

	bool controller::ShowBindingPanel(ControllerHandle_t controllerHandle) {
		return false;
	}

	std::uint64_t controller::GetActionSetHandle(const char* pszActionSetName) {
		return 0;
	}

	void controller::ActivateActionSet(ControllerHandle_t controllerHandle, std::uint64_t actionSetHandle) {}

	std::uint64_t controller::GetCurrentActionSet(ControllerHandle_t controllerHandle) {
		return 0;
	}

	std::uint64_t controller::GetDigitalActionHandle(const char* pszActionName) {
		return 0;
	}

	std::uint64_t controller::GetDigitalActionData(ControllerHandle_t controllerHandle, std::uint64_t digitalActionHandle) {
		return 0;
	}

	int controller::GetDigitalActionOrigins(ControllerHandle_t controllerHandle, std::uint64_t actionSetHandle, std::uint64_t digitalActionHandle,
		std::uint64_t* originsOut)
	{
		return 0;
	}

	std::uint64_t controller::GetAnalogActionHandle(const char* pszActionName) {
		return 0;
	}

	std::uint64_t controller::GetAnalogActionData(ControllerHandle_t controllerHandle, std::uint64_t analogActionHandle) {
		return 0;
	}

	int controller::GetAnalogActionOrigins(ControllerHandle_t controllerHandle, std::uint64_t actionSetHandle, std::uint64_t analogActionHandle,
		std::uint64_t* originsOut)
	{
		return 0;
	}

	void controller::StopAnalogActionMomentum(ControllerHandle_t controllerHandle, std::uint64_t eAction) {}

	void controller::TriggerHapticPulse(ControllerHandle_t controllerHandle, std::uint64_t eTargetPad, unsigned short usDurationMicroSec) {}
}
