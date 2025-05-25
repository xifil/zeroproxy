#include "common.hpp"
#include "component/lua_hook.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <memory/memory.hpp>

namespace lua_hook {
	namespace {
		utils::hook::detour lua_l_open_lib_hook;

		std::vector<std::tuple<utils::hook::detour&, std::string, void*>> queued_hooks{};

		void lua_l_open_lib_stub(iw8::lua_State* s, const char* lib_name, const iw8::luaL_Reg* l, std::uint32_t n_up) {
			if (lib_name != nullptr) {
				for (iw8::luaL_Reg* f = const_cast<iw8::luaL_Reg*>(l); f; ++f) {
					if (f->name_ == nullptr) {
						break;
					}

					std::string full_name = std::format("{}.{}", lib_name, f->name_);
					std::uintptr_t func_addr = PTR_AS(std::uintptr_t, f->func_);

					for (auto& [detour, name, target] : queued_hooks) {
						if (name == full_name) {
							detour.create(func_addr, target);
							break;
						}
					}
				}
			}

			return lua_l_open_lib_hook.invoke<void>(s, lib_name, l, n_up);
		}
	}

	void create(utils::hook::detour& detour, const std::string& name, void* target) {
		return queued_hooks.push_back({ detour, name, target });
	}

	struct component final : generic_component {
		void post_unpack() override {
			lua_l_open_lib_hook.create(game::luaL_openlib, lua_l_open_lib_stub);
		}
	};
}

REGISTER_COMPONENT(lua_hook::component)
