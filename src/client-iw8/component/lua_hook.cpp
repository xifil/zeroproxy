#include "common.hpp"
#include "component/lua_hook.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <memory/memory.hpp>
#include <utils/string.hpp>

namespace lua_hook {
	namespace {
		utils::hook::detour lua_l_load_file_hook;
		utils::hook::detour lua_l_open_lib_hook;

		std::vector<std::tuple<utils::hook::detour&, std::string, void*>> queued_hooks{};

		void load_custom_lua(iw8::lua_State* s) {
			std::string custom_code = R"(
PlayerData_IO_Original = PlayerData.BFFBGAJGD
PlayerData.BFFBGAJGD = function(controller, source)
	if source ~= 0 then
		return PlayerData_IO_Original(controller, source)
	end
	
	local return_data = {}
	return_data.spData = {}
	return_data.spData.civiliansKilledGradeBest = {}
	return_data.spData.currentMission = {
		get = function()
			return "none"
		end
	}
	
	return return_data
end

SPSharedUtils.GetMissionStateForLevel = function(level, controller)
	return "complete"
end)";
			game::luaL_loadbuffer(s, custom_code.c_str(), custom_code.size(), custom_code.c_str());
		}

		int lua_l_load_file_stub(iw8::lua_State* s, const char* file_name) {
			auto res = lua_l_load_file_hook.invoke<int>(s, file_name);
			if (file_name != nullptr) {
				if ("ui/widgets/mp/WarzoneOnboardingEndChoicePopup.lua"s == file_name) {
					load_custom_lua(s);
				}
			}
			return res;
		}

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
		queued_hooks.push_back({ detour, name, target });
	}

	struct component final : generic_component {
		void post_unpack() override {
			lua_l_load_file_hook.create(game::luaL_loadfile, lua_l_load_file_stub);
			lua_l_open_lib_hook.create(game::luaL_openlib, lua_l_open_lib_stub);

			iw8::LUIMethod<iw8::LUIGlobalPackage>* cmd = *game::LUIMethod_LUIGlobalPackage_list;
			while (cmd) {
				auto func_name = cmd->get_name(game::unk_EncryptionKey);
				if (func_name) {
					for (auto& [detour, name, target] : queued_hooks) {
						if (name == func_name) {
							detour.create(PTR_AS(std::uintptr_t, cmd->func_), target);
							break;
						}
					}
				}
				cmd = cmd->next_;
			}
		}
	};
}

REGISTER_COMPONENT(lua_hook::component)
