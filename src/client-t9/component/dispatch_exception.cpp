#include "common.hpp"
#include "component/dispatch_exception.hpp"

#include <exception/filter.hpp>
#include <loader/component_loader.hpp>
#include <memory/memory.hpp>
#include <memory/signature_store.hpp>
#include <utils/hook.hpp>

namespace dispatch_exception {
	namespace {
		std::vector<exception_hijack> exception_hijack_store{};

		void* rtl_dispatch_exception;
		utils::hook::detour rtl_dispatch_exception_hook;

		NTSTATUS nt_continue(PCONTEXT thread_context, BOOLEAN raise_alert) {
			static auto func = utils::nt::library("ntdll.dll").get_proc<decltype(&nt_continue)>("NtContinue");
			return func(thread_context, raise_alert);
		}

		bool rtl_dispatch_exception_stub(EXCEPTION_RECORD* record, CONTEXT* ctx) {
			static utils::nt::library game{};

			if (record->ExceptionCode == STATUS_INVALID_HANDLE) {
				nt_continue(ctx, FALSE);
				return true;
			}

			if (game.is_address_in_range(PTR_AS(std::uintptr_t, record->ExceptionAddress))) {
				for (auto& hijack : exception_hijack_store) {
					if (record->ExceptionCode == hijack.exception_code_ && hijack.is_viable_callback_(ctx)) {
						if (hijack.validate_context_callback_(ctx)) {
							hijack.redirected_callback_();
						}
						else {
							EXCEPTION_POINTERS ptrs{ record, ctx };
							exception::filter(&ptrs);
						}

						nt_continue(ctx, FALSE);
						return true;
					}
				}
			}

			return rtl_dispatch_exception_hook.invoke<bool>(record, ctx);
		}
	}

	void register_exception_hijack(long target_exception_code, std::function<bool(CONTEXT*)> is_viable_callback,
		std::function<bool(CONTEXT*)> validate_context_callback, std::function<void()> redirected_callback)
	{
		exception_hijack_store.push_back(exception_hijack(target_exception_code, is_viable_callback, validate_context_callback, redirected_callback));
	}

	struct component final : generic_component {
		void post_unpack() override {
			memory::signature_store batch{ utils::nt::library("ntdll.dll") };
			batch.add("RtlDispatchException", &rtl_dispatch_exception, "E9 ? ? ? ? 48 83 C4 ? 59", [](memory::scanned_result<void> res) {
				return res.add(1).rip();
			});
			batch.scan_all();

			rtl_dispatch_exception_hook.create(rtl_dispatch_exception, rtl_dispatch_exception_stub);
		}
	};
}

REGISTER_COMPONENT(dispatch_exception::component)