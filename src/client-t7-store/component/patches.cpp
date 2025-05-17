#include "common.hpp"

#include "component/scheduler.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>
#include <utils/string.hpp>

#include <version.hpp>

namespace patches {
	namespace {
		utils::hook::detour com_print_message_hook;

		utils::hook::iat_detour create_window_ex_a_hook;
		utils::hook::iat_detour set_window_text_a_hook;

		HWND game_window = nullptr;

		void com_print_message_stub(int channel, int console_type, const char* message, int unk) {
			std::string message_str = message;
			if (utils::string::ends_with(message_str, "\n")) {
				message_str = message_str.substr(0, message_str.size() - 1);
			}

			message_str = utils::string::replace(message_str, "^1", ANSI_FG_RGB(255, 92, 92));
			message_str = utils::string::replace(message_str, "^2", ANSI_FG_RGB(0, 255, 0));
			message_str = utils::string::replace(message_str, "^3", ANSI_FG_RGB(230, 200, 0));
			message_str = utils::string::replace(message_str, "^4", ANSI_FG_RGB(0, 0, 255));
			message_str = utils::string::replace(message_str, "^5", ANSI_FG_RGB(59, 188, 243));
			message_str = utils::string::replace(message_str, "^6", ANSI_FG_RGB(255, 92, 255));
			message_str = utils::string::replace(message_str, "^7", ANSI_FG_RGB(255, 255, 255));

			LOG("Component/Patches", DEBUG, "[game log@{}/{}]: {}", channel, console_type, message_str);
			com_print_message_hook.invoke<void>(channel, console_type, message, unk);
		}

		HWND create_window_ex_a_stub(DWORD dw_ex_style, LPCSTR lp_class_name, LPCSTR lp_window_name, DWORD dw_style, int x, int y, int n_width, int n_height,
			HWND hwnd_parent, HMENU h_menu, HINSTANCE h_instance, LPVOID lp_param)
		{
			auto res = create_window_ex_a_hook.invoke<HWND>(dw_ex_style, lp_class_name, lp_window_name, dw_style, x, y, n_width, n_height, hwnd_parent, h_menu,
				h_instance, lp_param);

			if (strcmp(lp_class_name, "CoDBlackOps") == 0) {
				game_window = res;
			}

			return res;
		}

		BOOL set_window_text_a_stub(HWND h_wnd, LPCSTR lp_string) {
			LPCSTR lp_string_patched = lp_string;
			if (h_wnd == game_window) {
				lp_string_patched = "t7s by lifix and luxploit | " GIT_DESCRIBE;
			}

			return set_window_text_a_hook.invoke<BOOL>(h_wnd, lp_string_patched);
		}
	}

	struct component final : generic_component {
		void post_load() override {
			com_print_message_hook.create(game::Com_PrintMessage, com_print_message_stub);
			create_window_ex_a_hook.create(utils::nt::library(), "user32.dll", "CreateWindowExA", create_window_ex_a_stub);
			set_window_text_a_hook.create(utils::nt::library(), "user32.dll", "SetWindowTextA", set_window_text_a_stub);
		}
	};
}

REGISTER_COMPONENT(patches::component)