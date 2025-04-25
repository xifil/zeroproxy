#include "common.hpp"

#include <exception/filter.hpp>
#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

#include <types.h>
#include <extern.h>

namespace exception_filter {
	namespace {
		uint64_t get_register_value(const CONTEXT* ctx, ud_type reg) {
			switch (reg) {
			case UD_R_RAX:
				return ctx->Rax;
			case UD_R_RBX:
				return ctx->Rbx;
			case UD_R_RCX:
				return ctx->Rcx;
			case UD_R_RDX:
				return ctx->Rdx;
			case UD_R_RSI:
				return ctx->Rsi;
			case UD_R_RDI:
				return ctx->Rdi;
			case UD_R_RSP:
				return ctx->Rsp;
			case UD_R_RBP:
				return ctx->Rbp;
			case UD_R_R8:
				return ctx->R8;
			case UD_R_R9:
				return ctx->R9;
			case UD_R_R10:
				return ctx->R10;
			case UD_R_R11:
				return ctx->R11;
			case UD_R_R12:
				return ctx->R12;
			case UD_R_R13:
				return ctx->R13;
			case UD_R_R14:
				return ctx->R14;
			case UD_R_R15:
				return ctx->R15;
			default:
				return 0;
			}
		}

		void set_register_value(CONTEXT* ctx, ud_type reg, uint64_t val) {
			switch (reg) {
			case UD_R_RAX:
				ctx->Rax = val;
				break;
			case UD_R_RBX:
				ctx->Rbx = val;
				break;
			case UD_R_RCX:
				ctx->Rcx = val;
				break;
			case UD_R_RDX:
				ctx->Rdx = val;
				break;
			case UD_R_RSI:
				ctx->Rsi = val;
				break;
			case UD_R_RDI:
				ctx->Rdi = val;
				break;
			case UD_R_RSP:
				ctx->Rsp = val;
				break;
			case UD_R_RBP:
				ctx->Rbp = val;
				break;
			case UD_R_R8:
				ctx->R8 = val;
				break;
			case UD_R_R9:
				ctx->R9 = val;
				break;
			case UD_R_R10:
				ctx->R10 = val;
				break;
			case UD_R_R11:
				ctx->R11 = val;
				break;
			case UD_R_R12:
				ctx->R12 = val;
				break;
			case UD_R_R13:
				ctx->R13 = val;
				break;
			case UD_R_R14:
				ctx->R14 = val;
				break;
			case UD_R_R15:
				ctx->R15 = val;
				break;
			}
		}

		long __stdcall exception_filter_with_patch(EXCEPTION_POINTERS* inf) {
			if (inf->ExceptionRecord->ExceptionCode == EXCEPTION_ILLEGAL_INSTRUCTION) {
				auto ctx = inf->ContextRecord;

				ud_t ud;
				ud_init(&ud);
				ud_set_mode(&ud, 64);
				ud_set_input_buffer(&ud, (uint8_t*)ctx->Rip, 7);

				if (ud_disassemble(&ud)) {
					if (ud.mnemonic == UD_Ipopcnt) {
						const ud_operand_t& dst = ud.operand[0];
						const ud_operand_t& src = ud.operand[1];

						uint64_t val = 0;

						if (src.type == UD_OP_MEM) {
							uint64_t base = 0, index = 0, addr = 0;
							if (src.base != UD_NONE) {
								base = get_register_value(ctx, src.base);
							}
							if (src.index != UD_NONE) {
								index = get_register_value(ctx, src.index);
							}

							addr = base + (index * src.scale) + src.lval.sdword;

							val = DEREF_PTR_AS(uint64_t, addr);
						}
						else if (src.type == UD_OP_REG) {
							val = get_register_value(ctx, src.base);
						}
						else {
							return EXCEPTION_CONTINUE_SEARCH;
						}

						uint64_t result = 0;
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
			return SetUnhandledExceptionFilter(exception_filter_with_patch);
		}
	}

	struct component final : generic_component {
		void post_load() override {
			utils::nt::library game{};
			utils::hook::set(game.get_iat_entry("kernel32.dll", "SetUnhandledExceptionFilter"), set_unhandled_exception_filter_stub);
		}
	};
}

REGISTER_COMPONENT(exception_filter::component)