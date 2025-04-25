#include "common.hpp"

#include "component/scheduler.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

namespace patches {
	namespace {
		utils::hook::detour cl_get_local_client_sign_in_state_hook;
		utils::hook::detour dw_get_log_on_status_hook;
		utils::hook::detour live_is_user_signed_in_to_demonware_hook;
		utils::hook::detour unk_is_user_signed_in_to_bnet_hook;

		int cl_get_local_client_sign_in_state_stub(int controller_index) {
			static bool signed_in = false;
			if (!signed_in) {
				int arr_elem_size = 0;

				if (identification::game::is(identification::game::version::iw8::v1_20_4_7623265_REPLAY, identification::game::version::iw8::v1_20_4_7623265_SHIP)) {
					arr_elem_size = 0x3A;
				}
				else if (identification::game::is(identification::game::version::iw8::v1_38_3_9489393, identification::game::version::iw8::v1_44_0_10435696)) {
					arr_elem_size = 0x46;
				}

				if (arr_elem_size != 0) {
					game::unk_SignInState[arr_elem_size * controller_index] = 2;
					signed_in = true;
				}
			}
			return cl_get_local_client_sign_in_state_hook.invoke<int>(controller_index);
		}

		iw8::DWOnlineStatus dw_get_log_on_status_stub(int controller_index) {
			return iw8::DWOnlineStatus::DW_LIVE_CONNECTED;
		}

		bool live_is_user_signed_in_to_demonware_stub(int controller_index) {
			return true;
		}

		bool unk_is_user_signed_in_to_bnet_stub() {
			return true;
		}

		void mystery_function_stub() {
			// do nothing
		}
	}

	struct component final : generic_component {
		void post_load() override {
			// stop the game from crashing on launch by skipping this one function - still unclear what it actually does.
			switch (identification::game::get_version()) {
			case identification::game::version::iw8::v1_20_4_7623265_REPLAY:
				utils::hook::jump(0x3061A0_b, mystery_function_stub);
				break;
			case identification::game::version::iw8::v1_20_4_7623265_SHIP:
				utils::hook::set(0x3DF4548_b, mystery_function_stub);
				break;
			default:
				LOG("Component/Patches", WARN, "Failed to patch \"mystery function\" - if you're on Windows 11, there is a crash most likely imminent.");
				break;
			}
		}

		void post_unpack() override {
			//cl_get_local_client_sign_in_state_hook.create(game::CL_GetLocalClientSignInState, cl_get_local_client_sign_in_state_stub);
			dw_get_log_on_status_hook.create(game::dwGetLogOnStatus, dw_get_log_on_status_stub);
			live_is_user_signed_in_to_demonware_hook.create(game::Live_IsUserSignedInToDemonware, live_is_user_signed_in_to_demonware_stub);
			//unk_is_user_signed_in_to_bnet_hook.create(game::unk_IsUserSignedInToBnet, unk_is_user_signed_in_to_bnet_stub);

			scheduler::loop([] {
				static bool finished_auth_patch = false;
				if (finished_auth_patch) {
					return;
				}

				static int frame_counter = 0;
				if (frame_counter != 500) {
					frame_counter++;
					return;
				}

				iw8::XUID xuid;
				xuid.random_xuid();
				std::uint64_t xuid_magic = 0x11CB1243B8D7C31E;
				std::uint64_t xuid_id = xuid.id_ * xuid.id_;

				LOG("Component/Patches", INFO, "Patching auth...");
				game::unk_BNetClass->finished_auth_ = true;

				*game::unk_XUIDCheck1 = xuid_magic | xuid_id;

				// the below patch (0x14F05ACE8 @ 1.20.4.7623265-replay) seems to be replay only, with this being xref 5 of 6, however only 5 exist
				// in ship, and this is the one excluded.
				if (game::unk_XUIDCheck2 != nullptr) {
					*game::unk_XUIDCheck2 = xuid_magic | xuid_id;
				}

				(*game::s_presenceData)[0].current_.cross_title_presence_data_.platform_id_ = xuid_magic | xuid_id / 6;

				*game::s_isContentEnumerationFinished = true;
				game::unk_BNetClass->state_ = 2;
				game::unk_BNetClass->finished_auth_ = true;

				iw8::dvar_t* xp_dec_dc = game::Dvar_FindVarByName("NTTRLOPQKS");
				if (xp_dec_dc != nullptr) {
					xp_dec_dc->current_.enabled_ = false;
				}

				game::unk_BNetClass->var3_ = 0x795230F0;
				game::unk_BNetClass->var4_ = 0x1F;
				game::unk_BNetClass->var5_ = 0x00000000;

				finished_auth_patch = true;
			}, scheduler::pipeline::renderer);
		}
	};
}

REGISTER_COMPONENT(patches::component)