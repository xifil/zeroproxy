#pragma once

#include "com.hpp"

namespace utils {
	class progress_ui {
	public:
		progress_ui(bool headless);
		~progress_ui();

		void show(bool marquee, HWND parent = nullptr) const;

		void set_progress(std::size_t current, std::size_t max) const;
		void set_line(int line, const std::string& text) const;
		void set_title(const std::string& title) const;

		bool is_cancelled() const;

		operator bool() const {
			return this->dialog_;
		}

	private:
		CComPtr<IProgressDialog> dialog_{};
	};
}
