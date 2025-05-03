#include "common.hpp"

#include "component/scheduler.hpp"
#include "game/dvars.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <nt/process_environment_block.hpp>
#include <utils/hook.hpp>

namespace arxan {
	namespace {
		void restore_ntdll_dbg_functions() {
			static const char* functions[] = {
				"DbgBreakPoint",
				"DbgUserBreakPoint",
				"DbgUiConnectToDbg",
				"DbgUiContinue",
				"DbgUiConvertStateChangeStructure",
				"DbgUiDebugActiveProcess",
				"DbgUiGetThreadDebugObject",
				"DbgUiIssueRemoteBreakin",
				"DbgUiRemoteBreakin",
				"DbgUiSetThreadDebugObject",
				"DbgUiStopDebugging",
				"DbgUiWaitStateChange",
				"DbgPrintReturnControlC",
				"DbgPrompt"
			};

			using buffer = uint8_t[15];
			static utils::nt::library ntdll{ "ntdll.dll" };
			static buffer buffers[ARRAYSIZE(functions)] = {};
			static bool loaded = false;

			for (auto i = 0u; i < ARRAYSIZE(functions); ++i) {
				void* function_addr = ntdll.get_proc<void*>(functions[i]);
				if (!function_addr) {
					continue;
				}

				if (!loaded) {
					memcpy(buffers[i], function_addr, sizeof(buffer));
				}
				else {
					utils::hook::copy(function_addr, buffers[i], sizeof(buffer));
				}
			}

			loaded = true;
		}
	}

	struct component final : generic_component {
		component_priority priority() const override {
			return component_priority::arxan;
		}

		void post_load() override {
			auto* const peb = PTR_AS(nt::process_environment_block*, __readgsqword(0x60));
			peb->being_debugged_ = false;
			peb->nt_global_flag_ &= ~0x70;
			restore_ntdll_dbg_functions();
		}

		void post_unpack() override {
		}
	};
}

REGISTER_COMPONENT(arxan::component)