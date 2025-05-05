#include "common.hpp"

#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

namespace fastfiles {
	namespace {
		utils::hook::detour db_load_x_file_hook;

		int db_load_x_file_stub(const char* zone_name, iw8::XZoneMemory* zone_mem, iw8::XAssetList* asset_list, std::uint32_t zone_flags, bool was_paused,
			iw8::DB_FastFileFailureMode failure_mode, iw8::DB_AuthSignature* out_signature)
		{
			LOG("Component/FastFiles", INFO, "Loading fastfile {}...", zone_name == nullptr ? "<null>" : zone_name);
			int res = db_load_x_file_hook.invoke<int>(zone_name, zone_mem, asset_list, zone_flags, was_paused, failure_mode, out_signature);
			if (res != 0) {
				LOG("Component/FastFiles", WARN, "Loaded fastfile {} with non-zero code {}.", zone_name == nullptr ? "<null>" : zone_name, res);
			}
			return res;
		}
	}

	struct component final : client_component {
		void post_unpack() override {
			db_load_x_file_hook.create(game::DB_LoadXFile, db_load_x_file_stub);
		}
	};
}

REGISTER_COMPONENT(fastfiles::component)