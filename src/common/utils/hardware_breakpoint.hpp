#pragma once
#include <thread>
#include "nt.hpp"

namespace utils::hardware_breakpoint {
	enum condition {
		execute = 0,
		write = 1,
		read_write = 3
	};

	void set_branch_tracing(bool enabled, CONTEXT& context);
	void set_branch_tracing(bool enabled, std::uint32_t thread_id = GetCurrentThreadId());

	std::uint32_t activate(std::uint64_t address, std::uint32_t length, condition cond, CONTEXT& context);
	std::uint32_t activate(void* address, std::uint32_t length, condition cond, std::uint32_t thread_id = GetCurrentThreadId());
	std::uint32_t activate(std::uint64_t address, std::uint32_t length, condition cond, std::uint32_t thread_id = GetCurrentThreadId());

	void deactivate_address(std::uint64_t address, CONTEXT& context);
	void deactivate_address(void* address, std::uint32_t thread_id = GetCurrentThreadId());
	void deactivate_address(std::uint64_t address, std::uint32_t thread_id = GetCurrentThreadId());

	void deactivate(std::uint32_t index, CONTEXT& context);
	void deactivate(std::uint32_t index, std::uint32_t thread_id = GetCurrentThreadId());

	void deactivate_all(CONTEXT& context);
	void deactivate_all(std::uint32_t thread_id = GetCurrentThreadId());
}
