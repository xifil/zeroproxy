﻿#include "common_core.hpp"
#include "loader/component_loader.hpp"

#include "identification/client.hpp"
#include "identification/game.hpp"
#include "utils/nt.hpp"

namespace component_loader {
	namespace {
		bool post_load_phase_complete = false;
		bool post_unpack_phase_complete = false;
	
		std::vector<std::unique_ptr<generic_component>>& get_components() {
			using component_vector = std::vector<std::unique_ptr<generic_component>>;
			using component_vector_container = std::unique_ptr<component_vector, std::function<void(component_vector*)>>;

			static component_vector_container components(new component_vector, [](const component_vector* component_vector) {
				pre_destroy();
				delete component_vector;
			});

			return *components;
		}

		std::vector<std::pair<registration_functor, component_type>>& get_registration_functors() {
			static std::vector<std::pair<registration_functor, component_type>> functors;
			return functors;
		}

		void activate_component(std::unique_ptr<generic_component> component) {
			auto& components = get_components();
			components.push_back(std::move(component));

			std::ranges::stable_sort(components, [](const std::unique_ptr<generic_component>& a, const std::unique_ptr<generic_component>& b) {
				return a->priority() > b->priority();
			});
		}
	}

	void register_component(registration_functor functor, component_type type) {
		if (!get_components().empty()) {
			throw std::runtime_error("Registration is too late");
		}

		get_registration_functors().emplace_back(std::move(functor), type);
	}

	bool should_load() {
		auto target_game = identification::game::get_target_game();
		if (identification::game::is_game(target_game)) {
			return true;
		}

		auto client_name = identification::client::get_client_name();
		auto version = identification::game::get_version();
		if (version.version_ == "0.0.0.0") {
			return MessageBoxA(nullptr, "This client has been launched on an unknown game/game version. Try to load anyway?", client_name, MB_YESNO) == IDYES;
		}

		std::string message = std::format("You are trying to launch {} for {} on {}. Please delete {} download the correct client for {}.",
			client_name, target_game, version.game_, client_name, version.game_);

		MessageBoxA(nullptr, message.c_str(), client_name, MB_OK);
		return false;
	}

	bool activate(bool server) {
		static auto res = [server] {
			try {
				for (auto& functor : get_registration_functors()) {
					if (functor.second == component_type::any || server == (functor.second == component_type::server)) {
						activate_component(functor.first());
					}
				}
			}
			catch (premature_shutdown_trigger&) {
				return false;
			}
			catch (const std::exception& e) {
				utils::nt::show_error(e.what());
				return false;
			}

			return true;
		}();

		return res;
	}

	bool post_load() {
		static auto res = [] {
			try {
				for (const auto& component : get_components()) {
					component->post_load();
				}
			}
			catch (premature_shutdown_trigger&) {
				return false;
			}
			catch (const std::exception& e) {
				utils::nt::show_error(e.what());
				return false;
			}

			post_load_phase_complete = true;
			return true;
		}();

		return res;
	}

	void post_unpack() {
		static auto res = [] {
			try {
				for (const auto& component : get_components()) {
					component->post_unpack();
				}
			}
			catch (const std::exception& e) {
				utils::nt::show_error(e.what());
				return false;
			}

			post_unpack_phase_complete = true;
			return true;
		}();

		if (!res) {
			TerminateProcess(GetCurrentProcess(), 1);
		}
	}

	void pre_destroy() {
		static auto res = [] {
			try {
				for (const auto& component : get_components()) {
					component->pre_destroy();
				}
			}
			catch (const std::exception& e) {
				utils::nt::show_error(e.what());
				return false;
			}

			return true;
		}();

		if (!res) {
			TerminateProcess(GetCurrentProcess(), 1);
		}
	}

	bool is_post_load_phase_complete() {
		return post_load_phase_complete;
	}

	bool is_post_unpack_phase_complete() {
		return post_unpack_phase_complete;
	}

	void trigger_premature_shutdown() {
		throw premature_shutdown_trigger();
	}
}