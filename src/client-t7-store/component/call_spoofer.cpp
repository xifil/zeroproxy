#include "common.hpp"
#include "component/call_spoofer.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

namespace call_spoofer {
	const std::uintptr_t get_spoof_trampoline() {
		return 0x1027_b;
	}

	struct component final : generic_component {
		component_priority priority() const override {
			return component_priority::call_spoofer;
		}

		void post_load() override {
			utils::hook::set<std::uint32_t>(get_spoof_trampoline() - 2, 0x27FFFFFF);
		}
	};
}

REGISTER_COMPONENT(call_spoofer::component)
