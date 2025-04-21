#include "identification/game.hpp"
#include "memory/memory.hpp"

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

			if ("Black Ops II"s == get_target_game()) {
				auto changelist = memory::sig_scan<std::uint32_t*>(game, "8B 0D ? ? ? ? A1 ? ? ? ? 8B 15 ? ? ? ? 51");
				if (changelist.get() != nullptr) {
					return *changelist.add(7).rel().get();
				}
			}

			return checksum;
		}();

		return checksum_ret;
	}
}
