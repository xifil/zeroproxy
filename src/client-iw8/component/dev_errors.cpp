#include "common.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>
#include <utils/string.hpp>

namespace dev_errors {
	namespace {
		utils::hook::iat_detour message_box_w_hook;

		std::unordered_map<int, std::wstring> dev_error_list = {
			{ 6031, L"Fastfile is newer than client executable (XFILE_FF_HEADER_VERSION %d, expecting %d)" },
			{ 6032, L"Fastfile is out of date (XFILE_FF_HEADER_VERSION %d, expecting %d)" },
			{ 6033, L"FF magic was invalid" },
			{ 6034, L"%s is out of date (XFILE_VERSION %d, expecting %d)" },
			{ 6035, L"%s is newer than client executable (XFILE_VERSION %d, expecting %d)" },
			{ 6036, L"Unable to open" },
			{ 6037, L"Unable to read header" },
			{ 6039, L"XFILE_FD_HEADER_VERSION mismatch. Has '%d', wanted '%d'" },
			{ 6040, L"XFILE_DIFF_VERSION version mismatch. Has '%d', wanted '%d'" },
			{ 6041, L"Patch header data mismatch between current and prior patch" },
			{ 6042, L"Patch header data mismatch between base FF '%s' and current patch" }
		};

		int message_box_w_stub(HWND h_wnd, LPCWSTR lp_text, LPCWSTR lp_caption, UINT u_type) {
			if (lp_text != nullptr) {
				std::wstring text = lp_text;
				std::wregex regex(L"DEV ERROR (\\d+)");
				std::wsmatch match;

				if (std::regex_search(text, match, regex)) {
					int error_code = std::stoi(match[1].str());
					if (auto it = dev_error_list.find(error_code); it != dev_error_list.end()) {
						return message_box_w_hook.invoke<int>(h_wnd, utils::string::replace(text, match[0].str(), it->second).c_str(), lp_caption, u_type);
					}
				}
			}

			return message_box_w_hook.invoke<int>(h_wnd, lp_text, lp_caption, u_type);
		}
	}

	struct component final : client_component {
		void post_load() override {
			message_box_w_hook.create({}, "user32.dll", "MessageBoxW", message_box_w_stub);
		}
	};
}

REGISTER_COMPONENT(dev_errors::component)