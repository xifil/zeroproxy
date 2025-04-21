#include "common_core.hpp"
#include "logger/console.hpp"

#include "utils/nt.hpp"

namespace logger {
	void console::init(const std::string& title) {
		if (utils::nt::registry_key console_reg = utils::nt::open_or_create_registry_key(HKEY_CURRENT_USER, "Console")) {
			DWORD target_val = 1;
			RegSetValueExA(console_reg, "VirtualTerminalLevel", 0, REG_DWORD, PTR_AS(BYTE*, &target_val), sizeof(DWORD));
		}
		
		AllocConsole();
		freopen_s(PTR_AS(FILE**, stdout), "CONOUT$", "w", stdout);
		freopen_s(PTR_AS(FILE**, stdin), "CONIN$", "r", stdin);
		SetConsoleTitleA(title.data());
		SetConsoleOutputCP(CP_UTF8);
	}

	void console::destroy() {
		fclose(stdin);
		fclose(stdout);
		FreeConsole();
	}
	
	HANDLE console::get_output_handle() {
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}

	DWORD console::get_console_mode() {
		DWORD mode = 0;
		::GetConsoleMode(get_output_handle(), &mode);
		return mode;
	}

	void console::set_console_mode(DWORD console_mode) {
		::SetConsoleMode(get_output_handle(), console_mode);
	}

	void console::set_cursor_pos(COORD pos) {
		SetConsoleCursorPosition(get_output_handle(), pos);
	}

	COORD console::get_cursor_pos() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(get_output_handle(), &csbi)) {
			return csbi.dwCursorPosition;
		}

		return { -1, -1 };
	}

	std::string console::get_text_at_pos(COORD pos, int length) {
		if (length <= 0) {
			return "";
		}

		short length_i16 = static_cast<short>(length);

		CHAR_INFO* buffer = new CHAR_INFO[length];
		SMALL_RECT read_region = { pos.X, pos.Y, static_cast<short>(pos.X + length_i16 - 1), pos.Y };
		ReadConsoleOutputA(get_output_handle(), buffer, { length_i16, 1 }, { 0, 0 }, &read_region);

		std::string result;
		for (int i = 0; i < length; ++i) {
			result += buffer[i].Char.AsciiChar;
		}

		delete[] buffer;
		return result;
	}

	void input_thread() {
		while (true) {
			std::string input;
			std::getline(std::cin, input);
			if (console::on_input) {
				console::on_input(input);
			}
		}
	}

	void console::start_input_thread() {
		std::thread thread(input_thread);
		thread.detach();
	}

	void console::write(const std::string& text) {
		std::lock_guard lock(mutex);
		set_console_mode(get_console_mode() | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

		COORD cursor_pos = get_cursor_pos();
		COORD target_cursor_pos = { 0, cursor_pos.Y };
		std::string current_input = get_text_at_pos(target_cursor_pos, cursor_pos.X);
		set_cursor_pos(target_cursor_pos);
		std::cout << text << std::flush << std::endl;
		std::cout << current_input << std::flush;
	}
}
