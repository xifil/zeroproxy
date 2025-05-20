#include "common.hpp"
#include "game/game.hpp"

#include <engine/sce_pad/sce_pad_color.hpp>
#include <loader/component_loader.hpp>
#include <memory/memory.hpp>
#include <utils/hook.hpp>

namespace sce_pad {
	namespace {
		int last_lua_gamepad_index = 0;
		int last_cl_get_key_binding_internal_index = 0;
		int set_all_controllers_index = -1;

		utils::hook::detour cl_get_key_binding_internal_hook;
		utils::hook::detour c_scr_cmd_set_all_controllers_lightbar_color_hook;
		utils::hook::detour g_pad_reset_lightbar_color_hook;
		utils::hook::detour g_pad_set_lightbar_color_hook;

		utils::nt::library& get_lib_sce_pad() {
			static utils::nt::library lib_sce_pad("libScePad.dll");
			return lib_sce_pad;
		}

		int sce_pad_set_light_bar(int handle, sce_pad::sce_pad_color* light_bar) {
			return get_lib_sce_pad().invoke<int>("scePadSetLightBar", handle, light_bar);
		}

		int sce_pad_reset_light_bar(int handle) {
			return get_lib_sce_pad().invoke<int>("scePadResetLightBar", handle);
		}

		int controller_index_to_sce_pad_handle(int controller_index) {
			if (controller_index > 2 || controller_index < 0) {
				return -1;
			}

			if (!game::s_gamePads[controller_index].connected_) {
				return -1;
			}

			int pad_index = game::s_gamePads[controller_index].pad_index_;
			if (pad_index < 4 || pad_index >= 8) {
				return -1;
			}

			if (game::unk_PadHandles[pad_index].status_ < 0) {
				return -1;
			}

			return game::unk_PadHandles[pad_index].handle_id_;
		}

		int cl_get_key_binding_internal_stub(int local_client_num, const char* command, char** key_names, int game_pad_only, int bind_num) {
			last_cl_get_key_binding_internal_index = local_client_num;
			return cl_get_key_binding_internal_hook.invoke<int>(local_client_num, command, key_names, game_pad_only, bind_num);
		}

		void c_scr_cmd_set_all_controllers_lightbar_color_stub(std::uint32_t control) {
			set_all_controllers_index = 0;
			c_scr_cmd_set_all_controllers_lightbar_color_hook.invoke<void>(control);
		}

		void g_pad_reset_lightbar_color_stub() {
			g_pad_reset_lightbar_color_hook.invoke<void>();

			static utils::nt::library game{};
			static std::uintptr_t c_scr_cmd_set_all_controllers_lightbar_color = memory::sig_scan(game, "48 83 EB ? 75 ? 48 8B 4C 24").as<std::uintptr_t>();
			static std::uintptr_t c_scr_cmd_set_controller_lightbar_color = memory::sig_scan(game, "48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 33 D2 8D"
				" 4A ? E8 ? ? ? ? 83 F8").add(0x9D).as<std::uintptr_t>();

			int controller_index = -1;
			std::uintptr_t return_address = PTR_AS(std::uintptr_t, _ReturnAddress());
			if (return_address == c_scr_cmd_set_all_controllers_lightbar_color) {
				controller_index = set_all_controllers_index++;
			}
			else if (return_address == c_scr_cmd_set_controller_lightbar_color) {
				controller_index = game::Com_LocalClient_GetControllerIndex(game::Scr_GetInt(t7s::scriptInstance_t::SCRIPTINSTANCE_CLIENT, 0));
			}
			else if (controller_index > 2 || controller_index < 0) {
				controller_index = 0;
			}

			int sce_pad_handle = controller_index_to_sce_pad_handle(controller_index);
			if (sce_pad_handle < 0) {
				return;
			}

			sce_pad_reset_light_bar(sce_pad_handle);
		}

		void g_pad_set_lightbar_color_stub(int controller_index_in, t7s::vec3_t* color) {
			g_pad_set_lightbar_color_hook.invoke<void>(controller_index_in, color);

			static utils::nt::library game{};
			static std::uintptr_t c_scr_cmd_set_all_controllers_lightbar_color = memory::sig_scan(game, "EB ? E8 ? ? ? ? 48 83 EB").as<std::uintptr_t>();
			static std::uintptr_t c_scr_cmd_set_controller_lightbar_color = memory::sig_scan(game, "48 8B 4C 24 ? 48 33 CC E8 ? ? ? ? 48 83 C4 ? C3 E8 ? ? ? ?"
				" 48 8B 4C 24").as<std::uintptr_t>();

			int controller_index = controller_index_in;
			std::uintptr_t return_address = PTR_AS(std::uintptr_t, _ReturnAddress());
			if (return_address == c_scr_cmd_set_all_controllers_lightbar_color) {
				controller_index = set_all_controllers_index++;
			}
			else if (return_address == c_scr_cmd_set_controller_lightbar_color) {
				controller_index = game::Com_LocalClient_GetControllerIndex(game::Scr_GetInt(t7s::scriptInstance_t::SCRIPTINSTANCE_CLIENT, 0));
			}
			else if (controller_index > 2 || controller_index < 0) {
				controller_index = 0;
			}

			int sce_pad_handle = controller_index_to_sce_pad_handle(controller_index);
			if (sce_pad_handle < 0) {
				return;
			}

			sce_pad::sce_pad_color sce_color(color->x, color->y, color->z);
			sce_pad_set_light_bar(sce_pad_handle, sce_color.get_this());
		}
	}

	struct component final : generic_component {
		void post_load() override {
			cl_get_key_binding_internal_hook.create(game::CL_GetKeyBindingInternal, cl_get_key_binding_internal_stub);
			c_scr_cmd_set_all_controllers_lightbar_color_hook.create(game::CScrCmd_SetAllControllersLightbarColor,
				c_scr_cmd_set_all_controllers_lightbar_color_stub);
			g_pad_reset_lightbar_color_hook.create(game::GPad_ResetLightbarColor, g_pad_reset_lightbar_color_stub);
			g_pad_set_lightbar_color_hook.create(game::GPad_SetLightbarColor, g_pad_set_lightbar_color_stub);
		}
	};
}

//REGISTER_COMPONENT(sce_pad::component)
