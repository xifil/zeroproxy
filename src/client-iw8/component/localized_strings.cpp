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
		utils::hook::detour seh_string_ed_get_string_hook;

		using localized_map = std::vector<std::pair<std::regex, std::function<std::string(const original_localization&, const std::smatch&)>>>;
		utils::concurrency::container<localized_map> localized_overrides;

		const char* localize_string(const char* key, const char* original_value) {
			if (!key[1]) {
				if ((*key & 0x80) != 0) {
					return "t";
				}
				return key;
			}

			game::GamerProfile_SetDataByName(0, "acceptedEULA", 1.f);
			game::GamerProfile_SetDataByName(0, "hasEverPlayed_MainMenu", 1.f);

			return localized_overrides.access<const char*>([&](const localized_map& map) {
				const auto res = original_value;

				for (const auto& [regex, callback] : map) {
					std::string input = key;
					std::smatch match;
					if (std::regex_match(input, match, regex) && input.size() == match[0].str().size()) {
						original_localization original_loc = { input, res };
						return utils::string::va("%s", callback(original_loc, match).data());
					}
				}

				return res;
			});
		}

		iw8::XAssetHeader db_find_x_asset_header_stub(iw8::XAssetType type, const char* given_name, int allow_create_default) {
			auto res = db_find_x_asset_header_hook.invoke<iw8::XAssetHeader>(type, given_name, allow_create_default);

			if (type == iw8::XAssetType::ASSET_TYPE_LOCALIZE && res.data_ != nullptr) {
				res.localize_->value_ = localize_string(given_name, res.localize_->value_);
			}

			return res;
		}

		const char* seh_string_ed_get_string_stub(const char* psz_reference) {
			return localize_string(psz_reference, seh_string_ed_get_string_hook.invoke<const char*>(psz_reference));
		}
	}

	void override(const std::regex& exp, const std::function<std::string(const original_localization&, const std::smatch&)>& callback) {
		localized_overrides.access([&](localized_map& map) {
			map.push_back(std::make_pair(exp, callback));
		});
	}

	struct component final : generic_component {
		void post_unpack() override {
			if (game::DB_FindXAssetHeader != nullptr) {
				db_find_x_asset_header_hook.create(game::DB_FindXAssetHeader, db_find_x_asset_header_stub);
			}
			else if (game::SEH_StringEd_GetString != nullptr) {
				seh_string_ed_get_string_hook.create(game::SEH_StringEd_GetString, seh_string_ed_get_string_stub);
			}
		}
	};
}

REGISTER_COMPONENT(localized_strings::component)