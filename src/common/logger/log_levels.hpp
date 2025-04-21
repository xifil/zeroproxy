#pragma once
#include "common_core.hpp"
#include "logger/ansi.hpp"

namespace logger {
	class log_level {
	public:
		log_level(const std::string& label, const std::string& ansi_color, int index) {
			this->label_ = label;
			this->ansi_color_ = ansi_color;
			this->index_ = index;
		}

		std::string get_label() {
			return this->label_;
		}

		std::string get_ansi_color() {
			return this->ansi_color_;
		}

		bool operator==(int index) const {
			return this->index_ == index;
		}
	private:
		std::string label_{};
		std::string ansi_color_{};
		int index_{};
	};

	namespace levels {
#		ifdef DEBUG
#			undef DEBUG
#		endif
#		ifdef ERROR
#			undef ERROR
#		endif
		// Do not create log levels on the same line - it will not look good in code and will break my shortening
#		define CREATE_LOG_LEVEL(name, color) \
		inline int name##_INDEX = __LINE__;\
		inline log_level name = log_level(ANSI_STRINGIFY(name), color, name##_INDEX);
		CREATE_LOG_LEVEL(INFO, ANSI_FG_RGB(92, 150, 44))
		CREATE_LOG_LEVEL(WARN, ANSI_FG_RGB(166, 138, 13))
		CREATE_LOG_LEVEL(ERROR, ANSI_FG_RGB(240, 82, 79))
		CREATE_LOG_LEVEL(FATAL, ANSI_FG_STYLE_256(124))
		CREATE_LOG_LEVEL(TRACE, ANSI_FG_STYLE_256(214))
		CREATE_LOG_LEVEL(DEBUG, ANSI_FG_STYLE_256(243))
#		undef CREATE_LOG_LEVEL
	}
}