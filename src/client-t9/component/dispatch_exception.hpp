#pragma once
#include "common.hpp"

namespace dispatch_exception {
	class exception_hijack {
	public:
		exception_hijack(long target_exception_code, std::function<bool(CONTEXT*)> is_viable_callback, std::function<bool(CONTEXT*)> validate_context_callback,
			std::function<void()> redirected_callback)
			: exception_code_(target_exception_code)
			, is_viable_callback_(is_viable_callback)
			, validate_context_callback_(validate_context_callback)
			, redirected_callback_(redirected_callback)
		{}

		long exception_code_;
		std::function<bool(CONTEXT*)> is_viable_callback_;
		std::function<bool(CONTEXT*)> validate_context_callback_;
		std::function<void()> redirected_callback_;
	};

	void register_exception_hijack(long target_exception_code, std::function<bool(CONTEXT*)> is_viable_callback,
		std::function<bool(CONTEXT*)> validate_context_callback, std::function<void()> redirected_callback);
}
