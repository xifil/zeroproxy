﻿#include "common.hpp"
#include "component/scheduler.hpp"

#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>
#include <utils/concurrency.hpp>
#include <utils/thread.hpp>

namespace scheduler {
	namespace {
		struct task {
			std::function<bool()> handler{};
			std::chrono::milliseconds interval{};
			std::chrono::high_resolution_clock::time_point last_call{};
		};

		using task_list = std::vector<task>;

		class task_pipeline {
		public:
			void add(task&& task) {
				return new_callbacks_.access([&task](task_list& tasks) {
					tasks.emplace_back(std::move(task));
				});
			}

			void execute() {
				return callbacks_.access([&](task_list& tasks) {
					this->merge_callbacks();

					for (auto i = tasks.begin(); i != tasks.end();) {
						const auto now = std::chrono::high_resolution_clock::now();
						const auto diff = now - i->last_call;

						if (diff < i->interval) {
							++i;
							continue;
						}

						i->last_call = now;

						const auto res = i->handler();
						if (res == cond_end) {
							i = tasks.erase(i);
						}
						else {
							++i;
						}
					}
				});
			}

		private:
			utils::concurrency::container<task_list> new_callbacks_;
			utils::concurrency::container<task_list, std::recursive_mutex> callbacks_;

			void merge_callbacks() {
				return callbacks_.access([&](task_list& tasks) {
					return new_callbacks_.access([&](task_list& new_tasks) {
						tasks.insert(tasks.end(), std::move_iterator(new_tasks.begin()), std::move_iterator(new_tasks.end()));
						new_tasks = {};
					});
				});
			}
		};

		volatile bool kill = false;
		std::thread async_thread;
		task_pipeline pipelines[ENUM_UNDER(pipeline::count)];

		utils::hook::detour com_frame_try_block_function_hook;
		utils::hook::detour g_glass_update_hook;
		utils::hook::detour scr_place_end_frame_hook;
		utils::hook::detour ui_refresh_fullscreen_hook;

		void com_frame_try_block_function_stub() {
			com_frame_try_block_function_hook.invoke<void>();
			return execute(pipeline::main);
		}

		void g_glass_update_stub() {
			g_glass_update_hook.invoke<void>();
			return execute(pipeline::server);
		}

		void scr_place_end_frame_stub() {
			scr_place_end_frame_hook.invoke<void>();
			return execute(pipeline::renderer);
		}

		void ui_refresh_fullscreen_stub(std::uint32_t local_client_num) {
			execute(pipeline::renderer);
			return ui_refresh_fullscreen_hook.invoke<void>(local_client_num);
		}
	}

	void execute(const pipeline type) {
		assert(ENUM_UNDER(type) >= 0 && ENUM_UNDER(type) < ENUM_UNDER(pipeline::count));
		return pipelines[ENUM_UNDER(type)].execute();
	}

	void schedule(const std::function<bool()>& callback, const pipeline type, const std::chrono::milliseconds delay) {
		assert(ENUM_UNDER(type) >= 0 && ENUM_UNDER(type) < ENUM_UNDER(pipeline::count));

		task task;
		task.handler = callback;
		task.interval = delay;
		task.last_call = std::chrono::high_resolution_clock::now();

		return pipelines[ENUM_UNDER(type)].add(std::move(task));
	}

	void loop(const std::function<void()>& callback, const pipeline type, const std::chrono::milliseconds delay) {
		return schedule([callback]() {
			callback();
			return cond_continue;
		}, type, delay);
	}

	void once(const std::function<void()>& callback, const pipeline type, const std::chrono::milliseconds delay) {
		return schedule([callback]() {
			callback();
			return cond_end;
		}, type, delay);
	}

	struct component final : generic_component {
		void post_load() override {
			async_thread = utils::thread::create_named_thread("Async Scheduler", []() {
				while (!kill) {
					execute(pipeline::async);
					std::this_thread::sleep_for(10ms);
				}
			});

			if (!game::is_server()) {
				if (game::ScrPlace_EndFrame != nullptr) {
					scr_place_end_frame_hook.create(game::ScrPlace_EndFrame, scr_place_end_frame_stub);
				}
				else if (game::UI_RefreshFullscreen != nullptr) {
					ui_refresh_fullscreen_hook.create(game::UI_RefreshFullscreen, ui_refresh_fullscreen_stub);
				}
			}

			com_frame_try_block_function_hook.create(game::Com_Frame_Try_Block_Function, com_frame_try_block_function_stub);
			g_glass_update_hook.create(game::G_Glass_Update, g_glass_update_stub);
		}

		void pre_destroy() override {
			kill = true;
			if (async_thread.joinable()) {
				async_thread.join();
			}
		}
	};
}

REGISTER_COMPONENT(scheduler::component)