#include "common.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

namespace images {
	struct component final : generic_component {
		void post_load() override {
			if (identification::game::is(iw4_store_version::v2_0_6_SP)) {
				// Skip version check
				utils::hook::nop(0x51038_b, 6);
			}
		}
	};
}

REGISTER_COMPONENT(images::component)