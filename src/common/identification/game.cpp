﻿#include "identification/game.hpp"
#include "memory/memory.hpp"
#include "utils/string.hpp"

extern "C" const char* ext_get_target_game();

namespace identification::game {
	const char* get_target_game() {
		return ext_get_target_game();
	}

	std::uint32_t get_checksum() {
		static utils::nt::library game{};
		static std::uint32_t checksum = game.get_checksum();

		static auto checksum_ret = [] {
			auto it = std::ranges::find_if(version_list, [](const version::identifier& i) {
				return i == checksum;
			});
			
			if (it != version_list.end() && it._Unwrapped() != nullptr) {
				return checksum;
			}

#			if defined(_WIN64)
				if (utils::string::equals_any(get_target_game(), { "Black Ops II", "Black Ops III", "Ghosts", "Modern Warfare 2" })) {
					return static_cast<std::uint32_t>(game.get_nt_headers()->FileHeader.TimeDateStamp);
				}
#			else
				if ("Black Ops II"s == get_target_game()) {
					auto changelist = memory::sig_scan<std::uint32_t*>(game, "8B 0D ? ? ? ? A1 ? ? ? ? 8B 15 ? ? ? ? 51");
					if (changelist.get() != nullptr) {
						return *changelist.add(7).rel().get();
					}
				}
#			endif

			return checksum;
		}();

		return checksum_ret;
	}
}
