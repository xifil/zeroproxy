#include "common.hpp"
#include "component/localized_strings.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <utils/concurrency.hpp>
#include <utils/hook.hpp>
#include <utils/string.hpp>

namespace localized_strings {
	namespace {
		utils::hook::detour seh_string_ed_get_string_hook;

		using localized_map = std::vector<std::pair<std::regex, std::function<std::string(const original_localization&, const std::smatch&)>>>;
		utils::concurrency::container<localized_map> localized_overrides;

		const char* seh_string_ed_get_string_stub(const char* psz_reference) {
			if (!psz_reference[1]) {
				if ((*psz_reference & 0x80) != 0) {
					return "t";
				}
				return psz_reference;
			}

			return localized_overrides.access<const char*>([&](const localized_map& map) {
				const auto res = seh_string_ed_get_string_hook.invoke<const char*>(psz_reference);

				for (const auto& [regex, callback] : map) {
					std::string input = psz_reference;
					std::smatch match;
					if (std::regex_match(input, match, regex) && input.size() == match[0].str().size()) {
						original_localization original_loc = { input, res };
						return utils::string::va("%s", callback(original_loc, match).data());
					}
				}

				return res;
			});
		}
	}

	void override(const std::regex& exp, const std::function<std::string(const original_localization&, const std::smatch&)>& callback) {
		localized_overrides.access([&](localized_map& map) {
			map.push_back(std::make_pair(exp, callback));
		});
	}

	struct component final : generic_component {
		void post_load() override {
			seh_string_ed_get_string_hook.create(game::SEH_StringEd_GetString, seh_string_ed_get_string_stub);
		}
	};
}

REGISTER_COMPONENT(localized_strings::component)