#include "common.hpp"
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
				new_callbacks_.access([&task](task_list& tasks) {
					tasks.emplace_back(std::move(task));
				});
			}

			void execute() {
				callbacks_.access([&](task_list& tasks) {
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
				callbacks_.access([&](task_list& tasks) {
					new_callbacks_.access([&](task_list& new_tasks) {
						tasks.insert(tasks.end(), std::move_iterator(new_tasks.begin()), std::move_iterator(new_tasks.end()));
						new_tasks = {};
					});
				});
			}
		};

		volatile bool kill = false;
		std::thread async_thread;
		task_pipeline pipelines[ENUM_UNDER(pipeline::count)];

		utils::hook::detour cl_draw_screen_hook;
		utils::hook::detour main_frame_hook;

		void cl_draw_screen_stub(std::uint32_t local_client_num) {
			cl_draw_screen_hook.invoke<void>(local_client_num);
			execute(pipeline::renderer);
		}

		void g_clear_vehicle_inputs_stub() {
			//game::G_ClearVehicleInputs();
			execute(pipeline::server);
		}

		void main_frame_stub() {
			main_frame_hook.invoke<void>();
			execute(pipeline::main);
		}
	}

	void execute(const pipeline type) {
		assert(ENUM_UNDER(type) >= 0 && ENUM_UNDER(type) < ENUM_UNDER(pipeline::count));
		pipelines[ENUM_UNDER(type)].execute();
	}

	void schedule(const std::function<bool()>& callback, const pipeline type, const std::chrono::milliseconds delay) {
		assert(ENUM_UNDER(type) >= 0 && ENUM_UNDER(type) < ENUM_UNDER(pipeline::count));

		task task;
		task.handler = callback;
		task.interval = delay;
		task.last_call = std::chrono::high_resolution_clock::now();

		pipelines[ENUM_UNDER(type)].add(std::move(task));
	}

	void loop(const std::function<void()>& callback, const pipeline type, const std::chrono::milliseconds delay) {
		schedule([callback]() {
			callback();
			return cond_continue;
		}, type, delay);
	}

	void once(const std::function<void()>& callback, const pipeline type, const std::chrono::milliseconds delay) {
		schedule([callback]() {
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
				//cl_draw_screen_hook.create(game::CL_DrawScreen, cl_draw_screen_stub);
			}

			// Com_Frame_Try_Block_Function
			//main_frame_hook.create(game::select(0x1420F8E00, 0x1405020E0), main_frame_stub);

			//utils::hook::call(game::select(0x14225522E, 0x140538427), g_clear_vehicle_inputs_stub);
		}

		void pre_destroy() override {
			kill = true;
			if (async_thread.joinable()) {
				async_thread.join();
			}
		}
	};
}

//REGISTER_COMPONENT(scheduler::component)