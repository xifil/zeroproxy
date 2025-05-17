#include "common.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>
#include <utils/string.hpp>

namespace zones {
	namespace {
		utils::hook::detour fs_find_x_zone_hook;

		const char* fs_find_x_zone_stub(const char* file_name) {
            static char cd[MAX_PATH]{ 0 };
            memset(cd, 0, sizeof(cd));

            if (_getcwd(cd, MAX_PATH) == nullptr) {
				return fs_find_x_zone_hook.invoke<const char*>(file_name);
            }

			const char* zone_dir = utils::string::va("%s/zone", cd);
			const char* file = utils::string::va("%s/%s", zone_dir, file_name);
            if (std::filesystem::exists(file)) {
                return zone_dir;
            }

			return fs_find_x_zone_hook.invoke<const char*>(file_name);
		}
	}

	struct component final : generic_component {
		void post_load() override {
			fs_find_x_zone_hook.create(game::FS_FindXZone, fs_find_x_zone_stub);
		}
	};
}

REGISTER_COMPONENT(zones::component)