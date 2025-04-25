#include "common.hpp"

#include <exception/filter.hpp>
#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

#include <types.h>
#include <extern.h>

namespace exception_filter {
	namespace {
		utils::hook::iat_detour set_unhandled_exception_filter_hook;

		std::uint64_t* get_ctx_register_ptr(CONTEXT* ctx, ud_type reg) {
			static std::map<int, std::size_t> offset_map = {
				{ UD_R_RAX, offsetof(CONTEXT, Rax) },
				{ UD_R_RBX, offsetof(CONTEXT, Rbx) },
				{ UD_R_RCX, offsetof(CONTEXT, Rcx) },
				{ UD_R_RDX, offsetof(CONTEXT, Rdx) },
				{ UD_R_RSI, offsetof(CONTEXT, Rsi) },
				{ UD_R_RDI, offsetof(CONTEXT, Rdi) },
				{ UD_R_RSP, offsetof(CONTEXT, Rsp) },
				{ UD_R_RBP, offsetof(CONTEXT, Rbp) },
				{ UD_R_R8, offsetof(CONTEXT, R8) },
				{ UD_R_R9, offsetof(CONTEXT, R9) },
				{ UD_R_R10, offsetof(CONTEXT, R10) },
				{ UD_R_R11, offsetof(CONTEXT, R11) },
				{ UD_R_R12, offsetof(CONTEXT, R12) },
				{ UD_R_R13, offsetof(CONTEXT, R13) },
				{ UD_R_R14, offsetof(CONTEXT, R14) },
				{ UD_R_R15, offsetof(CONTEXT, R15) }
			};

			auto it = offset_map.find(reg);
			if (it == offset_map.end()) {
				return nullptr;
			}

			return PTR_AS(std::uint64_t*, PTR_AS(std::uintptr_t, ctx) + it->second);
		}

		std::uint64_t get_register_value(CONTEXT* ctx, ud_type reg) {
			auto it = get_ctx_register_ptr(ctx, reg);
			if (it == nullptr) {
				return 0;
			}

			return *it;
		}

		void set_register_value(CONTEXT* ctx, ud_type reg, std::uint64_t val) {
			auto it = get_ctx_register_ptr(ctx, reg);
			if (it == nullptr) {
				return;
			}

			*it = val;
		}

		long __stdcall exception_filter_with_patch(EXCEPTION_POINTERS* inf) {
			if (inf->ExceptionRecord->ExceptionCode == EXCEPTION_ILLEGAL_INSTRUCTION) {
				auto ctx = inf->ContextRecord;

				ud_t ud;
				ud_init(&ud);
				ud_set_mode(&ud, 64);
				ud_set_input_buffer(&ud, (std::uint8_t*)ctx->Rip, 7);

				if (ud_disassemble(&ud)) {
					if (ud.mnemonic == UD_Ipopcnt) {
						const ud_operand_t& dst = ud.operand[0];
						const ud_operand_t& src = ud.operand[1];

						std::uint64_t val = 0;

						if (src.type == UD_OP_MEM) {
							std::uint64_t base = 0, index = 0, addr = 0;
							if (src.base != UD_NONE) {
								base = get_register_value(ctx, src.base);
							}
							if (src.index != UD_NONE) {
								index = get_register_value(ctx, src.index);
							}

							addr = base + (index * src.scale) + src.lval.sdword;

							val = DEREF_PTR_AS(std::uint64_t, addr);
						}
						else if (src.type == UD_OP_REG) {
							val = get_register_value(ctx, src.base);
						}
						else {
							return EXCEPTION_CONTINUE_SEARCH;
						}

						std::uint64_t result = 0;
						while (val) {
							result += val & 1;
							val >>= 1;
						}

						if (dst.type == UD_OP_REG) {
							set_register_value(ctx, dst.base, result);
						}
						else {
							return EXCEPTION_CONTINUE_SEARCH;
						}

						ctx->Rip += ud_insn_len(&ud);

						return EXCEPTION_CONTINUE_EXECUTION;
					}
				}
			}

			return exception::filter(inf);
		}

		LPTOP_LEVEL_EXCEPTION_FILTER set_unhandled_exception_filter_stub(LPTOP_LEVEL_EXCEPTION_FILTER) {
			return set_unhandled_exception_filter_hook.invoke<LPTOP_LEVEL_EXCEPTION_FILTER>(exception_filter_with_patch);
		}
	}

	struct component final : generic_component {
		void post_load() override {
			set_unhandled_exception_filter_hook.create({}, "kernel32.dll", "SetUnhandledExceptionFilter", set_unhandled_exception_filter_stub);
		}
	};
}

REGISTER_COMPONENT(exception_filter::component)