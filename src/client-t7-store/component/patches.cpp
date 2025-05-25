#include "common.hpp"

#include "component/scheduler.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <memory/memory.hpp>
#include <utils/hook.hpp>
#include <utils/string.hpp>

#include <version.hpp>

namespace patches {
	namespace {
		utils::hook::detour bd_log_message_hook;
		utils::hook::detour com_print_message_hook;

		utils::hook::iat_detour create_window_ex_a_hook;
		utils::hook::iat_detour set_window_text_a_hook;

		HWND game_window = nullptr;

		void bd_log_message_stub(int type, const char* category, const char* source, const char* source_file, const char* source_function, int a6,
			const char* message, ...)
		{
			va_list args;
			va_start(args, message);

			char buffer[1024];
			vsnprintf(buffer, sizeof(buffer), message, args);

			va_end(args);

			LOG("Component/Patches", DEBUG, "[DW] [{}{}] [{}/{}]: {}", category, type, source, source_function, buffer);
			return bd_log_message_hook.invoke<void>(type, category, source, source_file, source_function, a6, "%s", buffer);
		}

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
			return com_print_message_hook.invoke<void>(channel, console_type, message, unk);
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
			utils::nt::library game{};

			bd_log_message_hook.create(game::bdLogMessage, bd_log_message_stub);
			com_print_message_hook.create(game::Com_PrintMessage, com_print_message_stub);
			create_window_ex_a_hook.create(game, "user32.dll", "CreateWindowExA", create_window_ex_a_stub);
			set_window_text_a_hook.create(game, "user32.dll", "SetWindowTextA", set_window_text_a_stub);

			utils::hook::set<std::uint8_t>(memory::sig_scan(game, "75 ? 83 25").get(), 0xEB);								// always enable ingame console
			utils::hook::set<std::uint8_t>(memory::sig_scan(game, "40 55 57 41 54 41 55 41 57 48 8D AC 24").get(), 0xC3);	// stub microphone enumeration

			/* fix mutex crash in xbox curl by making it a recursive mutex */
			auto non_recursive_lock_res = memory::sig_scan(game, "41 8D 57 ? E8 ? ? ? ? 90 48 8D 77");

			auto non_recursive_lock = non_recursive_lock_res.as<std::uintptr_t>();
			auto _mtx_init_in_situ = non_recursive_lock_res.add(5).rip().as<std::uintptr_t>();

			char mutex_patch[] = {
				0xBA, 0x02, 0x01, 0x00, 0x00	// mov edx, 0x00000102;
			};
			utils::hook::copy(non_recursive_lock, mutex_patch, ARRAYSIZE(mutex_patch));
			utils::hook::call(non_recursive_lock + ARRAYSIZE(mutex_patch), _mtx_init_in_situ);

			return scheduler::loop([] {
				static int affinity_state = 0;
				static ULONG_PTR process_affinity = 0;
				static ULONG_PTR system_affinity = 0;

				if (affinity_state > 1) {
					return;
				}

				if (affinity_state == 0) {
					if (GetProcessAffinityMask(GetCurrentProcess(), &process_affinity, &system_affinity)) {
						if (process_affinity) {
							ULONG_PTR affinity = process_affinity & (1 | 2 | 4 | 8);
							if (affinity) {
								if (SetProcessAffinityMask(GetCurrentProcess(), affinity)) {
									affinity_state++;
								}
							}
						}
					}
				}
				else if (affinity_state == 1) {
					if (SetProcessAffinityMask(GetCurrentProcess(), process_affinity)) {
						affinity_state++;
					}
				}
			}, scheduler::pipeline::async, 1000ms);
		}

		void post_unpack() override {
			utils::nt::library game{};

			/* patch in non-matching fastfiles (avoid "Fastfile archive checksum ([...]) does not match executable nor any permissible") */
			utils::hook::set<std::uint8_t>(memory::sig_scan(game, "74 ? 41 FF C3 49 83 C2").get(), 0xEB);
		}
	};
}

REGISTER_COMPONENT(patches::component)