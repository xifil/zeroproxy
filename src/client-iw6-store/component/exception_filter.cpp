#include "common.hpp"

#include <exception/filter.hpp>
#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

#include <types.h>
#include <extern.h>

namespace exception_filter {
	namespace {
		utils::hook::iat_detour set_unhandled_exception_filter_hook;

		LPTOP_LEVEL_EXCEPTION_FILTER set_unhandled_exception_filter_stub(LPTOP_LEVEL_EXCEPTION_FILTER) {
			return set_unhandled_exception_filter_hook.invoke<LPTOP_LEVEL_EXCEPTION_FILTER>(exception::filter);
		}
	}

	struct component final : generic_component {
		void post_load() override {
			set_unhandled_exception_filter_hook.create({}, "kernel32.dll", "SetUnhandledExceptionFilter", set_unhandled_exception_filter_stub);
		}
	};
}

REGISTER_COMPONENT(exception_filter::component)