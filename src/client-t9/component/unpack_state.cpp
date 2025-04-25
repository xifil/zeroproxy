#include "common.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

namespace unpack_state {
	namespace {
		utils::hook::iat_detour discord_create_hook;

		int /* EDiscordResult */ discord_create_stub(int /* DiscordVersion */ version, struct DiscordCreateParams* params, struct IDiscordCore** result) {
			component_loader::post_unpack();
			return discord_create_hook.invoke<int>(version, params, result);
		}
	}

	struct component final : generic_component {
		void post_load() override {
			discord_create_hook.create({}, "discord_game_sdk.dll", "DiscordCreate", discord_create_stub);
		}
	};
}

REGISTER_COMPONENT(unpack_state::component)