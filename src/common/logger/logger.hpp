#pragma once
#include "common_core.hpp"
#include "logger/console.hpp"
#include "logger/log_levels.hpp"

namespace logger {
	template <typename... Args>
	void print(const std::string& log_name, log_level level, const std::string_view& format, Args const &...args) {
		// TODO: Add caller check from backward-cpp
		std::string caller = "<unknown module>";

		auto message = std::vformat(format, std::make_format_args(args...));

		tm local_time;
		const time_t time_since_epoch = std::time(nullptr);
		localtime_s(&local_time, &time_since_epoch);

		auto console_timestamp = std::format("[{:0>2}:{:0>2}:{:0>2}]", local_time.tm_hour, local_time.tm_min, local_time.tm_sec);
		// TODO: Add log to file
		//auto file_timestamp = std::format("[{}-{}-{} {:0>2}:{:0>2}:{:0>2}]", local_time.tm_year + 1900, local_time.tm_mon + 1, local_time.tm_mday,
		//	local_time.tm_hour, local_time.tm_min, local_time.tm_sec);

		console::write(std::format(ANSI_FG_CYAN "{} " ANSI_RESET "{}[{}{}] " ANSI_RESET ANSI_FG_RGB(0, 163, 163) "({}) " ANSI_RESET "{}" ANSI_RESET,
			console_timestamp, level.get_ansi_color(), caller.compare("<unknown module>") ? (caller + "/").c_str() : "", level.get_label(), log_name, message));
	}
}

#define LOG(name, type, ...) logger::print(name, logger::levels::type, __VA_ARGS__)
