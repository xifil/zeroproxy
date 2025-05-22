#include "common.hpp"
#include "game/game.hpp"

#include <component/localized_strings.hpp>
#include <loader/component_loader.hpp>
#include <utils/concurrency.hpp>
#include <utils/hook.hpp>
#include <utils/string.hpp>

namespace localized_strings {
	namespace {
		utils::hook::detour db_find_x_asset_header_hook;

		using localized_map = std::vector<std::pair<std::regex, std::function<std::string(const original_localization&, const std::smatch&)>>>;
		utils::concurrency::container<localized_map> localized_overrides;

		t7s::XAssetHeader db_find_x_asset_header_stub(t7s::XAssetType type, const char* name, bool error_if_missing, int wait_time) {
			const auto res = db_find_x_asset_header_hook.invoke<t7s::XAssetHeader>(type, name, error_if_missing, wait_time);

			if (type != t7s::XAssetType::ASSET_TYPE_LOCALIZE_ENTRY || res.data_ == nullptr) {
				return res;
			}

			localized_overrides.access([&](const localized_map& map) {
				for (const auto& [regex, callback] : map) {
					std::string input = name;
					std::smatch match;
					if (std::regex_match(input, match, regex) && input.size() == match[0].str().size()) {
						original_localization original_loc = { input, res.localize_->value_ };
						res.localize_->value_ = utils::string::va("%s", callback(original_loc, match).data());
					}
				}
			});

			return res;
		}
	}

	void override(const std::regex& exp, const std::function<std::string(const original_localization&, const std::smatch&)>& callback) {
		localized_overrides.access([&](localized_map& map) {
			map.push_back(std::make_pair(exp, callback));
		});
	}

	struct component final : generic_component {
		void post_load() override {
			db_find_x_asset_header_hook.create(game::DB_FindXAssetHeader, db_find_x_asset_header_stub);
		}
	};
}

REGISTER_COMPONENT(localized_strings::component)