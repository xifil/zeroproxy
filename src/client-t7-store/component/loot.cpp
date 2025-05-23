#include "common.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <memory/memory.hpp>
#include <utils/hook.hpp>

namespace loot {
	namespace {
		utils::hook::detour lua_p_call_hook;

		int lua_p_call_stub(t7s::lua_State* s, long n_args, long n_results, long err_func) {
			auto res = lua_p_call_hook.invoke<int>(s, n_args, n_results, err_func);

			const char* source_data = nullptr;
			auto return_address = PTR_AS(std::uintptr_t, _ReturnAddress());

			static utils::nt::library game{};
			static auto ui_uieditor_conditions = memory::sig_scan(game, "0F 84 ? ? ? ? 48 8B 1D ? ? ? ? 48 8B 83").add(2).rip().sub(0x1F).as<std::uintptr_t>();
			static auto ui_ffotd_tu32 = memory::sig_scan(game, "90 48 8D 4D ? E8 ? ? ? ? EB ? BF").as<std::uintptr_t>();

			if (return_address == ui_uieditor_conditions) {
				source_data = R"(EnableGlobals()

function IsServerBrowserEnabled()
	return false
end

Engine.IsWeaponOptionLockedEntitlement = function()
	return false
end

local defaultEmblemsCached = nil
local function getAllDefaults()
	if defaultEmblemsCached ~= nil then
		return defaultEmblemsCached
	end
	
	local tbl = {}
	for i = 0, 750, 1 do
		local desc = Engine.TableLookupGetColumnValueForRow("gamedata/emblems/backgrounds.csv", i, 4)
		if Engine.TableLookupGetColumnValueForRow("gamedata/emblems/backgrounds.csv", i, 9) == "default" and "EM_BACK_CWL_default" ~= desc then
			local curTbl = {}
			curTbl.id = i
			curTbl.description = Engine.Localize(desc)
			curTbl.isBGLocked = false
			curTbl.entitlement = nil
			curTbl.isContractBg = false
			table.insert(tbl, curTbl)
		end
	end

	defaultEmblemsCached = tbl
	return tbl
end

local oldGBFCN = Engine.GetBackgroundsForCategoryName
Engine.GetBackgroundsForCategoryName = function(arg0, arg1)
	if arg1 == "default" then
		return getAllDefaults()
	end
	return oldGBFCN(arg0, arg1)
end)";
			}
			else if (return_address == ui_ffotd_tu32) {
				source_data = R"(EnableGlobals()

require("ui.t7.utility.storeutility")

CoD.BlackMarketUtility.IsItemLocked = function()
	return false
end

CoD.StoreUtility.IsInventoryItemPurchased = function
	return true
end

CoD.StoreUtility.IsInventoryItemVisible = function
	return true
end

CoD.SpecialCallingCards = {})";
			}

			if (source_data != nullptr) {
				s->global_->bytecode_sharing_mode_ = t7s::hks::BytecodeSharingMode::HKS_BYTECODE_SHARING_ON;
				t7s::hks::CompilerSettings hks_compiler_settings;
				int load_res = game::hksI_hksL_loadbuffer(s, &hks_compiler_settings, source_data, strlen(source_data), source_data);
				if (load_res == 0) {
					load_res = game::hks_vm_call_internal(s, 0, 0, 0);
				}
				s->global_->bytecode_sharing_mode_ = t7s::hks::BytecodeSharingMode::HKS_BYTECODE_SHARING_SECURE;
			}

			return res;
		}
	}

	struct component final : generic_component {
		void post_load() override {
			lua_p_call_hook.create(game::lua_pcall, lua_p_call_stub);
		}

		void post_unpack() override {
			game::Dvar_SetFromStringByNameFromSource("ui_allLootUnlocked", "1", t7s::DvarSetSource::DVAR_SOURCE_INTERNAL, 0);
			game::Dvar_SetFromStringByNameFromSource("loot_unlockUnreleasedLoot", "1", t7s::DvarSetSource::DVAR_SOURCE_INTERNAL, 0);
		}
	};
}

REGISTER_COMPONENT(loot::component)
