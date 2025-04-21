#include "common_core.hpp"
#include "exception/filter.hpp"
#include "utils/nt.hpp"

namespace exception {
	namespace {
		void* init_dbg_help() {
			static class init_dbg_help_ {
			public:
				init_dbg_help_() {
					SymInitialize(GetCurrentProcess(), nullptr, FALSE);
				}

				~init_dbg_help_() {
					SymCleanup(GetCurrentProcess());
				}
			} init_dbg_help;
			return &init_dbg_help;
		}
	}

	void ensure_dbg_help() {
		(void)init_dbg_help();
	}

	long WINAPI filter(EXCEPTION_POINTERS* inf) {
		ensure_dbg_help();

		const char* exception_code_name;
		switch (inf->ExceptionRecord->ExceptionCode) {
		case EXCEPTION_ACCESS_VIOLATION:
			exception_code_name = "Access violation";
			break;
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
			exception_code_name = "Array bounds exceeded";
			break;
		case EXCEPTION_BREAKPOINT:
			exception_code_name = "Breakpoint";
			break;
		case EXCEPTION_DATATYPE_MISALIGNMENT:
			exception_code_name = "Data type misalignment";
			break;
		case EXCEPTION_FLT_DENORMAL_OPERAND:
			exception_code_name = "Float denormal operand";
			break;
		case EXCEPTION_FLT_DIVIDE_BY_ZERO:
			exception_code_name = "Float / 0";
			break;
		case EXCEPTION_FLT_INEXACT_RESULT:
			exception_code_name = "Float inexact result";
			break;
		case EXCEPTION_FLT_INVALID_OPERATION:
			exception_code_name = "Float invalid operation";
			break;
		case EXCEPTION_FLT_OVERFLOW:
			exception_code_name = "Float overflow";
			break;
		case EXCEPTION_FLT_STACK_CHECK:
			exception_code_name = "Float stack check";
			break;
		case EXCEPTION_FLT_UNDERFLOW:
			exception_code_name = "Float underflow";
			break;
		case EXCEPTION_ILLEGAL_INSTRUCTION:
			exception_code_name = "Illegal instruction";
			break;
		case EXCEPTION_IN_PAGE_ERROR:
			exception_code_name = "In-page error";
			break;
		case EXCEPTION_INT_DIVIDE_BY_ZERO:
			exception_code_name = "Int / 0";
			break;
		case EXCEPTION_INT_OVERFLOW:
			exception_code_name = "Integer overflow";
			break;
		case EXCEPTION_INVALID_DISPOSITION:
			exception_code_name = "Invalid disposition";
			break;
		case EXCEPTION_NONCONTINUABLE_EXCEPTION:
			exception_code_name = "Non-continuable exception";
			break;
		case EXCEPTION_PRIV_INSTRUCTION:
			exception_code_name = "Private instruction";
			break;
		case EXCEPTION_SINGLE_STEP:
			exception_code_name = "Single step";
			break;
		case EXCEPTION_STACK_OVERFLOW:
			exception_code_name = "Stack overflow";
			break;
		default:
			exception_code_name = "<unknown>";
			break;
		}

		utils::nt::library game{};
		utils::nt::library client = utils::nt::library(client_module);

		std::string message = "Unhandled exception caught. Instead of giving you absolutely nothing:\n";
		message += std::format("{} region: 0x" FMT_PTR " -> 0x" FMT_PTR "\n", game.get_name(),
			PTR_AS(std::uintptr_t, game.get_ptr()), PTR_AS(std::uintptr_t, game.get_ptr()) + game.get_optional_header()->SizeOfImage);
		message += std::format("{} region: 0x" FMT_PTR " -> 0x" FMT_PTR "\n", client.get_name(),
			PTR_AS(std::uintptr_t, client.get_ptr()), PTR_AS(std::uintptr_t, client.get_ptr()) + client.get_optional_header()->SizeOfImage);
		message += "---- Exception Record ----\n";
		message += std::format("Exception code: {} (0x{:08X})\n", exception_code_name, inf->ExceptionRecord->ExceptionCode);
		message += std::format("Exception flags: 0x{:08X}\n", inf->ExceptionRecord->ExceptionFlags);
		message += std::format("Exception address: {}\n", and_rel(PTR_AS(std::uintptr_t, inf->ExceptionRecord->ExceptionAddress)));
		message += std::format("Number of parameters: {}\n", inf->ExceptionRecord->NumberParameters);
		for (auto x = 0ul; x < std::min(inf->ExceptionRecord->NumberParameters, 15ul /*EXCEPTION_MAXIMUM_PARAMETERS*/); x++) {
			message += std::format(" > Parameter {}: {}\n", x, and_rel(inf->ExceptionRecord->ExceptionInformation[x]));
		}
		message += "----- Context Record -----\n";
#		if defined(_WIN64)
			message += std::format("P1Home: {}\n", and_rel(inf->ContextRecord->P1Home));
			message += std::format("P2Home: {}\n", and_rel(inf->ContextRecord->P2Home));
			message += std::format("P3Home: {}\n", and_rel(inf->ContextRecord->P3Home));
			message += std::format("P4Home: {}\n", and_rel(inf->ContextRecord->P4Home));
			message += std::format("P5Home: {}\n", and_rel(inf->ContextRecord->P5Home));
			message += std::format("P6Home: {}\n", and_rel(inf->ContextRecord->P6Home));

			message += std::format("Context flags: 0x{:08X}\n", inf->ContextRecord->ContextFlags);
			message += std::format("MxCsr: 0x{:08X}\n", inf->ContextRecord->MxCsr);

			message += std::format("SegCs: 0x{:04X}\n", inf->ContextRecord->SegCs);
			message += std::format("SegDs: 0x{:04X}\n", inf->ContextRecord->SegDs);
			message += std::format("SegEs: 0x{:04X}\n", inf->ContextRecord->SegEs);
			message += std::format("SegFs: 0x{:04X}\n", inf->ContextRecord->SegFs);
			message += std::format("SegGs: 0x{:04X}\n", inf->ContextRecord->SegGs);
			message += std::format("SegSs: 0x{:04X}\n", inf->ContextRecord->SegSs);
			message += std::format("EFlags: 0x{:08X}\n", inf->ContextRecord->EFlags);

			message += std::format("Dr0: {}\n", and_rel(inf->ContextRecord->Dr0));
			message += std::format("Dr1: {}\n", and_rel(inf->ContextRecord->Dr1));
			message += std::format("Dr2: {}\n", and_rel(inf->ContextRecord->Dr2));
			message += std::format("Dr3: {}\n", and_rel(inf->ContextRecord->Dr3));
			message += std::format("Dr6: {}\n", and_rel(inf->ContextRecord->Dr6));
			message += std::format("Dr7: {}\n", and_rel(inf->ContextRecord->Dr7));

			message += std::format("Rax: {}\n", and_rel(inf->ContextRecord->Rax));
			message += std::format("Rcx: {}\n", and_rel(inf->ContextRecord->Rcx));
			message += std::format("Rdx: {}\n", and_rel(inf->ContextRecord->Rdx));
			message += std::format("Rbx: {}\n", and_rel(inf->ContextRecord->Rbx));
			message += std::format("Rsp: {}\n", and_rel(inf->ContextRecord->Rsp));
			message += std::format("Rbp: {}\n", and_rel(inf->ContextRecord->Rbp));
			message += std::format("Rsi: {}\n", and_rel(inf->ContextRecord->Rsi));
			message += std::format("Rdi: {}\n", and_rel(inf->ContextRecord->Rdi));
			message += std::format("R8: {}\n", and_rel(inf->ContextRecord->R8));
			message += std::format("R9: {}\n", and_rel(inf->ContextRecord->R9));
			message += std::format("R10: {}\n", and_rel(inf->ContextRecord->R10));
			message += std::format("R11: {}\n", and_rel(inf->ContextRecord->R11));
			message += std::format("R12: {}\n", and_rel(inf->ContextRecord->R12));
			message += std::format("R13: {}\n", and_rel(inf->ContextRecord->R13));
			message += std::format("R14: {}\n", and_rel(inf->ContextRecord->R14));
			message += std::format("R15: {}\n", and_rel(inf->ContextRecord->R15));

			message += std::format("Rip: {}\n", and_rel(inf->ContextRecord->Rip));

			message += std::format("VectorControl: {}\n", and_rel(inf->ContextRecord->VectorControl));

			message += std::format("DebugControl: {}\n", and_rel(inf->ContextRecord->DebugControl));
			message += std::format("LastBranchToRip: {}\n", and_rel(inf->ContextRecord->LastBranchToRip));
			message += std::format("LastBranchFromRip: {}\n", and_rel(inf->ContextRecord->LastBranchFromRip));
			message += std::format("LastExceptionToRip: {}\n", and_rel(inf->ContextRecord->LastExceptionToRip));
			message += std::format("LastExceptionFromRip: {}\n", and_rel(inf->ContextRecord->LastExceptionFromRip));

			message += "------- Other Info -------\n";
			STACKFRAME64 stackFrame = { 0 };
			stackFrame.AddrPC.Offset = inf->ContextRecord->Rip;
			stackFrame.AddrPC.Mode = AddrModeFlat;
			stackFrame.AddrFrame.Offset = inf->ContextRecord->Rbp;
			stackFrame.AddrFrame.Mode = AddrModeFlat;
			stackFrame.AddrStack.Offset = inf->ContextRecord->Rsp;
			stackFrame.AddrStack.Mode = AddrModeFlat;

			std::size_t functionCount = 0;
			while (StackWalk64(IMAGE_FILE_MACHINE_AMD64, GetCurrentProcess(), GetCurrentThread(),
				&stackFrame, inf->ContextRecord, nullptr, SymFunctionTableAccess64, SymGetModuleBase64, nullptr))
			{
				functionCount++;
				message += std::format("Function address [{}]: {}\n", functionCount, and_rel(stackFrame.AddrPC.Offset));
			}
#		else
			message += std::format("Context flags: 0x{:08X}\n", inf->ContextRecord->ContextFlags);

			message += std::format("Dr0: {}\n", and_rel(inf->ContextRecord->Dr0));
			message += std::format("Dr1: {}\n", and_rel(inf->ContextRecord->Dr1));
			message += std::format("Dr2: {}\n", and_rel(inf->ContextRecord->Dr2));
			message += std::format("Dr3: {}\n", and_rel(inf->ContextRecord->Dr3));
			message += std::format("Dr6: {}\n", and_rel(inf->ContextRecord->Dr6));
			message += std::format("Dr7: {}\n", and_rel(inf->ContextRecord->Dr7));

			message += std::format("SegGs: 0x{:08X}\n", inf->ContextRecord->SegGs);
			message += std::format("SegFs: 0x{:08X}\n", inf->ContextRecord->SegFs);
			message += std::format("SegEs: 0x{:08X}\n", inf->ContextRecord->SegEs);
			message += std::format("SegDs: 0x{:08X}\n", inf->ContextRecord->SegDs);
			
			message += std::format("Edi: {}\n", and_rel(inf->ContextRecord->Edi));
			message += std::format("Esi: {}\n", and_rel(inf->ContextRecord->Esi));
			message += std::format("Ebx: {}\n", and_rel(inf->ContextRecord->Ebx));
			message += std::format("Edx: {}\n", and_rel(inf->ContextRecord->Edx));
			message += std::format("Ecx: {}\n", and_rel(inf->ContextRecord->Ecx));
			message += std::format("Eax: {}\n", and_rel(inf->ContextRecord->Eax));
		
			message += std::format("Ebp: {}\n", and_rel(inf->ContextRecord->Ebp));
			message += std::format("Eip: {}\n", and_rel(inf->ContextRecord->Eip));
			message += std::format("SegCs: 0x{:08X}\n", inf->ContextRecord->SegCs);
			message += std::format("EFlags: 0x{:08X}\n", inf->ContextRecord->EFlags);
			message += std::format("Esp: {}\n", and_rel(inf->ContextRecord->Esp));
			message += std::format("SegSs: 0x{:04X}\n", inf->ContextRecord->SegSs);
#		endif

		MessageBoxA(nullptr, message.c_str(), "iw8-mod exception handler", MB_OK);
		return EXCEPTION_EXECUTE_HANDLER;
	}
}
