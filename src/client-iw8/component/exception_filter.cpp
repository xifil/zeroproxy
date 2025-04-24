#include "common.hpp"

#include <exception/filter.hpp>
#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

namespace exception_filter {
	namespace {
		LPTOP_LEVEL_EXCEPTION_FILTER set_unhandled_exception_filter_stub(LPTOP_LEVEL_EXCEPTION_FILTER) {
			return SetUnhandledExceptionFilter(exception::filter);
		}
	}

	struct component final : generic_component {
		void post_load() override {
			utils::nt::library game{};
//			utils::hook::set(game.get_iat_entry("kernel32.dll", "SetUnhandledExceptionFilter"), set_unhandled_exception_filter_stub);

			auto entry = game.get_iat_entry("kernel32.dll", "SetUnhandledExceptionFilter");

			DWORD protect;
			VirtualProtect(reinterpret_cast<void*>(entry), sizeof(*entry), PAGE_EXECUTE_READWRITE, &protect);
			//this->m_Original = *entry;
			//T::m_Original = reinterpret_cast<decltype(T::m_Original)>(this->m_Original);
			*entry = set_unhandled_exception_filter_stub;
			VirtualProtect(reinterpret_cast<void*>(entry), sizeof(*entry), protect, &protect);
		}
	};
}

//REGISTER_COMPONENT(exception_filter::component)