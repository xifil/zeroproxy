#include "common.hpp"
#include "game/game.hpp"

#include <memory/memory.hpp>
#include <loader/component_loader.hpp>
#include <utils/hook.hpp>
#include <utils/string.hpp>

namespace content {
	namespace {
		void spoof_owns_content() {
			for (auto i = 0; i < 5; i++) {
				game::unk_OwnedContent[i] = 0x01;
			}
		}

		bool content_do_we_have_content_pack_stub() {
			spoof_owns_content();
			return true;
		}

		std::uint64_t content_get_available_content_packs_stub(char a1) {
			static auto v7_ptr = memory::sig_scan(utils::nt::library(), "48 8D 15 ? ? ? ? 0F 1F 44 00 ? 4D 3B CB").add(3).rip().as<std::uint8_t*>();

			auto mask = game::s_contentPackMetaData;
			auto v7 = v7_ptr;
			for (auto i = 0; i < 11; i++) {
				*v7 = 1;
				v7 += 130;
				mask += 20;
			}

			spoof_owns_content();
			return 0xFFFFFFFFFFFFFFFF;
		}

		bool content_has_entitlement_ownership_by_ref_stub() {
			return true;
		}

		bool ms_store_owns_content_stub() {
			spoof_owns_content();
			return true;
		}
	}

	struct component final : generic_component {
		void post_load() override {
			utils::hook::jump(game::Content_DoWeHaveContentPack, content_do_we_have_content_pack_stub);
			utils::hook::jump(game::Content_HasEntitlementOwnershipByRef, content_has_entitlement_ownership_by_ref_stub);
			utils::hook::jump(game::MSStore_OwnsContent, ms_store_owns_content_stub);
		}

		void post_unpack() override {
			utils::hook::jump(game::Content_GetAvailableContentPacks, content_get_available_content_packs_stub);
			spoof_owns_content();
		}
	};
}

REGISTER_COMPONENT(content::component)
