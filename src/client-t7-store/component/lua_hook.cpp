#include "common.hpp"
#include "component/lua_hook.hpp"

#include <loader/component_loader.hpp>
#include <memory/memory.hpp>

namespace lua_hook {
	namespace {
		std::vector<std::tuple<utils::hook::detour&, std::string, void*>> queued_hooks{};
	}

	void create(utils::hook::detour& detour, const std::string& name, void* target) {
		queued_hooks.push_back({ detour, name, target });
	}

	struct component final : generic_component {
		component_priority priority() const override {
			return component_priority::lua_hook;
		}

		void post_unpack() override {
			static utils::nt::library game{};

			std::vector<memory::scanned_result<void>> results = memory::vectored_sig_scan(game, "48 8B 05 ? ? ? ? 48 89 05 ? ? ? ? 48 8D 05 ? ? ? ?"
				" 48 89 05 ? ? ? ? C3 CC CC CC", std::numeric_limits<std::size_t>::max());

			for (auto& result : results) {
				const char** function_name = result.add(0x11).rip().as<const char**>();
				for (auto& [detour, name, target] : queued_hooks) {
					if (function_name != nullptr && name == *function_name) {
						detour.create(result.add(0x11).rip().add(0x8).rel().get(), target);
						break;
					}
				}
			}
		}
	};
}

REGISTER_COMPONENT(lua_hook::component)
