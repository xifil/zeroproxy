#include "common.hpp"

#include "component/scheduler.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>
#include <utils/string.hpp>

namespace console {
	namespace {
		bool input_has_n_params(std::vector<std::string> parts, std::size_t n) {
			if (parts.size() > n) {
				return true;
			}

			LOG("Component/Console", DEBUG, "Command \"{}\" requires at least {} parameters.", parts.at(0), n);
			return false;
		}

		void on_input(std::string input) {
			std::vector<std::string> input_parts = utils::string::split(input, ' ');
			std::vector<std::string> input_params{};
			std::string input_cmd = input_parts.at(0);
			std::string input_params_all = "";
			for (std::size_t x = 1; x < input_parts.size(); x++) {
				input_params.push_back(input_parts.at(x));
				if (x > 1) {
					input_params_all += " ";
				}
				input_params_all += input_parts.at(x);
			}

			if (input_cmd == "unlockall") {
				return game::Cbuf_AddText("seta unlockAllItems 1");
			}

			if (input_cmd == "openmenu" && input_has_n_params(input_parts, 1)) {
				return scheduler::once([=] {
					auto menu_name = input_params.at(0);
					game::LUI_OpenMenu(iw8::LocalClientNum_t::LOCAL_CLIENT_0, menu_name.c_str(), FALSE, FALSE, FALSE);
					LOG("Component/Console", DEBUG, "Opened menu: {}", menu_name);
				}, scheduler::pipeline::renderer);
			}

			return game::Cbuf_AddText(input.c_str());
		}
	}

	struct component final : generic_component {
		void post_load() override {
			logger::console::on_input = on_input;
			logger::console::start_input_thread();
		}
	};
}

REGISTER_COMPONENT(console::component)