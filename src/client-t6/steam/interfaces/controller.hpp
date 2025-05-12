#pragma once

namespace steam {
	using ControllerHandle_t = std::uint64_t;

	class controller {
	public:
		~controller() = default;

		virtual bool Init();
		virtual bool Shutdown();
		virtual void RunFrame();
		virtual int GetConnectedControllers(ControllerHandle_t* handlesOut);
		virtual bool ShowBindingPanel(ControllerHandle_t controllerHandle);
		virtual std::uint64_t GetActionSetHandle(const char* pszActionSetName);
		virtual void ActivateActionSet(ControllerHandle_t controllerHandle, std::uint64_t actionSetHandle);
		virtual std::uint64_t GetCurrentActionSet(ControllerHandle_t controllerHandle);
		virtual std::uint64_t GetDigitalActionHandle(const char* pszActionName);
		virtual std::uint64_t GetDigitalActionData(ControllerHandle_t controllerHandle, std::uint64_t digitalActionHandle);
		virtual int GetDigitalActionOrigins(ControllerHandle_t controllerHandle, std::uint64_t actionSetHandle, std::uint64_t digitalActionHandle,
			std::uint64_t* originsOut);
		virtual std::uint64_t GetAnalogActionHandle(const char* pszActionName);
		virtual std::uint64_t GetAnalogActionData(ControllerHandle_t controllerHandle, std::uint64_t analogActionHandle);
		virtual int GetAnalogActionOrigins(ControllerHandle_t controllerHandle, std::uint64_t actionSetHandle, std::uint64_t analogActionHandle,
			std::uint64_t* originsOut);
		virtual void StopAnalogActionMomentum(ControllerHandle_t controllerHandle, std::uint64_t eAction);
		virtual void TriggerHapticPulse(ControllerHandle_t controllerHandle, std::uint64_t eTargetPad, unsigned short usDurationMicroSec);
	};
}
