#include "common.hpp"
#include "steam/interface.hpp"

#include <extern.h>
#include <types.h>
#include <utils/memory.hpp>
#include <utils/nt.hpp>

namespace steam {
	interface::interface()
		: interface(nullptr)
	{}

	interface::interface(void* interface_ptr)
		: interface_ptr_(static_cast<void***>(interface_ptr))
	{}

	interface::operator bool() const {
		return this->interface_ptr_ != nullptr;
	}

	interface::method interface::find_method(const std::string& name) {
		const auto method_entry = this->methods_.find(name);
		if (method_entry != this->methods_.end()) {
			return method_entry->second;
		}

		return this->search_method(name);
	}

	interface::method interface::search_method(const std::string& name) {
		if (!utils::memory::is_bad_read_ptr(this->interface_ptr_)) {
			auto vftbl = *this->interface_ptr_;
			std::size_t cur_entry = 0;

			while (!utils::memory::is_bad_read_ptr(vftbl) && !utils::memory::is_bad_code_ptr(*vftbl)) {
				cur_entry++;
				const auto ptr = *vftbl;
				const auto result = this->analyze_method(ptr);
				if (result.name_found) {
					const method method_result{ *vftbl, result.param_size };
					this->methods_[result.name] = method_result;
					
					//LOG("SteamInterface", DEBUG, "{} [{}] = {}", result.name, cur_entry, and_rel(PTR_AS(std::uintptr_t, method_result.pointer)));

					if (result.name == name) {
						return method_result;
					}
				}

				++vftbl;
			}
		}

		return {};
	}

	interface::method_result interface::analyze_method(const void* method_ptr) {
		method_result result{};
		if (utils::memory::is_bad_code_ptr(method_ptr)) {
			return result;
		}

		ud_t ud;
		ud_init(&ud);
		ud_set_mode(&ud, sizeof(std::uintptr_t) * 8);
		ud_set_pc(&ud, reinterpret_cast<uint64_t>(method_ptr));
		ud_set_input_buffer(&ud, static_cast<const uint8_t*>(method_ptr), INT32_MAX);

		while (true) {
			ud_disassemble(&ud);

			if (ud_insn_mnemonic(&ud) == UD_Iret && !result.param_size_found) {
#				if defined(_WIN64)
					break;
#				else
					const ud_operand* operand = ud_insn_opr(&ud, 0);
					if (operand && operand->type == UD_OP_IMM && operand->size == 16) {
						result.param_size = operand->lval.uword;
					}
					else {
						result.param_size = 0;
					}

					result.param_size_found = true;
#				endif
			}

#			if defined(_WIN64)
				if (ud_insn_mnemonic(&ud) == UD_Ilea && !result.name_found) {
					const auto* operand = ud_insn_opr(&ud, 1);
					if (operand && operand->type == UD_OP_MEM && operand->base == UD_R_RIP) {
						auto* operand_ptr = reinterpret_cast<char*>(ud_insn_len(&ud) + ud_insn_off(&ud) + operand->lval.sdword);
						if (!utils::memory::is_bad_read_ptr(operand_ptr) && utils::memory::is_rdata_ptr(operand_ptr)) {
							result.name = operand_ptr;
							
							result.name_found = true;
							result.param_size_found = true;
						}
					}
				}
#			else
				if (ud_insn_mnemonic(&ud) == UD_Ipush && !result.name_found) {
					const auto operand = ud_insn_opr(&ud, 0);
					if (operand->type == UD_OP_IMM && operand->size == 32) {
						char* operand_ptr = reinterpret_cast<char*>(operand->lval.udword);
						if (!utils::memory::is_bad_read_ptr(operand_ptr) && utils::memory::is_rdata_ptr(operand_ptr)) {
							result.name = operand_ptr;
							result.name_found = true;
						}
					}
				}
#			endif

			if (*reinterpret_cast<unsigned char*>(ud.pc) == 0xCC) {
				break; // int 3
			}

			if (result.name_found && result.param_size_found) {
				break;
			}
		}

		return result;
	}
}
