#pragma once
#include "common_core.hpp"

namespace logger::console {
	void init(const std::string& title);
	void destroy();

	HANDLE get_output_handle();
	DWORD get_console_mode();
	void set_console_mode(DWORD console_mode);

	void set_cursor_pos(COORD pos);
	COORD get_cursor_pos();
	std::string get_text_at_pos(COORD pos, int length);

	void start_input_thread();

	void write(const std::string& text);

	inline std::function<void(std::string)> on_input{};
	inline std::mutex mutex{};
}