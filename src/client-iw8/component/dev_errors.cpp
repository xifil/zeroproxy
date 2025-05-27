#include "common.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>
#include <utils/string.hpp>

namespace dev_errors {
	namespace {
		utils::hook::iat_detour message_box_w_hook;

		std::unordered_map<int, std::wstring> dev_error_list = {
			{ 2276, L"Must be called on a client entity." },
			{ 2277, L"Non local players are not supported for this call." },
			{ 2278, L"Must be called on a client entity." },
			{ 2279, L"Non local players are not supported for this call." },
			{ 2280, L"Must be called on a client entity." },
			{ 2281, L"Non local players are not supported for this call." },
			{ 2538, L"divide by 0" },
			{ 2539, L"%g out of range" },
			{ 2540, L"%g out of range" },
			{ 2545, L"wrong number of arguments to vectornormalize!" },
			{ 2546, L"Wrong number of arguments to GenerateAxisFromForwardVector" },
			{ 2547, L"Wrong number of arguments to GenerateAxisFromUpVector" },
			{ 2548, L"wrong number of arguments to vectortoyaw!" },
			{ 2549, L"wrong number of arguments to vectortopitch!" },
			{ 2550, L"wrong number of arguments to vectorlerp" },
			{ 2551, L"Zero length vector was passed as first parameter!" },
			{ 2554, L"Incorrect number of parameters for ProjectileIntercept." },
			{ 2555, L"wrong number of arguments to anglestoup!" },
			{ 2556, L"Wrong number of arguments to AngleLerpQuat( <startAngles>, <end>, <maxAngleDelta> )" },
			{ 2557, L"Wrong number of arguments to AngleLerpQuatFrac( <startAngles>, <end>, <fraction> )" },
			{ 2558, L"wrong number of arguments to axistoangles" },
			{ 2559, L"wrong number of arguments to vectortoangle!" },
			{ 2560, L"string too long" },
			{ 2561, L"string too long" },
			{ 2562, L"string too long" },
			{ 2563, L"assert fail" },
			{ 2564, L"assert fail: %s" },
			{ 2565, L"assert fail: %s" },
			{ 2566, L"USAGE: tableLookup( filename, searchColumnNum, searchValue, returnValueColumnNum )\n" },
			{ 2568, L"USAGE: tableLookupByRow( filename, rowNum, returnValueColumnNum )\n" },
			{ 2569, L"USAGE: tableLookup( filename, searchColumnNum, searchValue, returnValueColumnNum )\n" },
			{ 2570, L"USAGE: tableLookupByRow( filename, rowNum, returnValueColumnNum )\n" },
			{ 2571, L"USAGE: tableLookupRowNum( filename, searchColumnNum, searchValue )\n" },
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
						return message_box_w_hook.invoke<int>(h_wnd, utils::string::replace(text, match[0].str(),
							std::format(L"[{}] {}", error_code, it->second)).c_str(), lp_caption, u_type);
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