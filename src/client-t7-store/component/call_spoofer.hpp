#pragma once
#include "common.hpp"

#include <utils/hook.hpp>

extern "C" void* _spoofer_stub();

namespace call_spoofer {
	const std::uintptr_t get_spoof_trampoline();

	template <typename Ret, typename... Args>
	static inline auto shellcode_stub_helper(const void* shell, Args... args) -> Ret {
		auto fn = (Ret(*)(Args...))(shell);
		return fn(args...);
	}

	template <std::size_t Argc, typename>
	struct argument_remapper {
		template <typename Ret, typename First, typename Second, typename Third, typename Fourth, typename... Pack>
		static auto do_call(const void* shell, void* shell_param, First first, Second second, Third third, Fourth fourth, Pack... pack) -> Ret {
			return shellcode_stub_helper<Ret, First, Second, Third, Fourth, void*, void*, Pack...>(shell, first, second, third, fourth, shell_param,
				nullptr, pack...);
		}
	};

	template <std::size_t Argc>
	struct argument_remapper<Argc, std::enable_if_t<Argc <= 4>> {
		template <typename Ret, typename First = void*, typename Second = void*, typename Third = void*, typename Fourth = void*>
		static auto do_call(const void* shell, void* shell_param, First first = First{}, Second second = Second{}, Third third = Third{},
			Fourth fourth = Fourth{}) -> Ret
		{
			return shellcode_stub_helper<Ret, First, Second, Third, Fourth, void*, void*>(shell, first, second, third, fourth, shell_param, nullptr);
		}
	};

	template <typename Ret, typename... Args>
	static inline auto spoof_call_trampoline(const void* trampoline, Ret(*fn)(Args...), Args... args) -> Ret {
		struct shell_params {
			const void* trampoline;
			void* function;
			void* rbx;
		};

		shell_params p{ trampoline, reinterpret_cast<void*>(fn) };
		using mapper = argument_remapper<sizeof...(Args), void>;
		return mapper::template do_call<Ret, Args...>((const void*)&::_spoofer_stub, &p, args...);
	}

	template <typename Ret, typename... Args>
	static inline auto spoof_call(Ret(*fn)(Args...), Args... args) -> Ret {
		return spoof_call_trampoline(PTR_AS(void*, get_spoof_trampoline()), fn, args...);
	}

	template <typename Ret, typename... Args>
	static inline auto spoof_hook_invoke(const utils::hook::detour& detour, Args... args) -> Ret {
		return spoof_call(detour.get<Ret(Args...)>(), args...);
	}
}
