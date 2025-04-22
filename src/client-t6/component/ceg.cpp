#include "common.hpp"

#include <loader/component_loader.hpp>
#include <memory/memory.hpp>
#include <utils/hook.hpp>

namespace ceg {
	namespace {
		using memcpy_ogT = int(void* src, void* dst);
		memcpy_ogT* memcpy_og = nullptr;

		std::uintptr_t unk_addr_store = 0;
		char zone_file_mem_buf[16];
		void* zone_file_mem;

		class ceg_sig_replace {
		public:
			ceg_sig_replace(const std::string& signature, int replace_offset, const std::string& replace)
				: signature_(signature)
				, replace_offset_(replace_offset)
				, new_(replace)
			{}

			bool patch() {
				auto res = memory::vectored_sig_scan({}, this->signature_, UINT_MAX);
				if (res.empty()) {
					return false;
				}

				for (auto& res_in : res) {
					res_in = res_in.add(this->replace_offset_);

					auto replace_data = memory::masked_signature_from_string(this->new_).data_;
					utils::hook::copy(res_in.get(), replace_data.data(), replace_data.size());
				}

				return true;
			}
		private:
			std::string signature_;
			int replace_offset_;
			std::string new_;
		};

		void disable_hardware_breakpoints(PCONTEXT ctx) {
			ctx->Dr0 = 0;
			ctx->Dr1 = 0;
			ctx->Dr2 = 0;
			ctx->Dr3 = 0;
			ctx->Dr7 &= 0xFFFFFFAA;
		}

		int unk_sub_1002F5E0(DWORD* a1, char a2, char a3, int a4) {
			*(DWORD*)a1 = (a4 << a2) | *(DWORD*)a1 & ~(((1 << a3) - 1) << a2);
			return a4 << a2;
		}

		void assign_hardware_breakpoint(PCONTEXT ctx, DWORD addr) {
#			if !defined(_WIN64)
				int v2; // ecx@7
				int v3; // eax@15
				char v4; // [sp+Ch] [bp-114h]@1
				int v5; // [sp+D0h] [bp-50h]@18
				int v6; // [sp+DCh] [bp-44h]@18
				int v7; // [sp+E8h] [bp-38h]@10
				unsigned __int8 v8; // [sp+F7h] [bp-29h]@1
				char v9; // [sp+103h] [bp-1Dh]@1
				char v10; // [sp+10Fh] [bp-11h]@1
				char v11; // [sp+11Bh] [bp-5h]@1

				v11 = 0;
				v10 = 0;
				v9 = 0;
				v8 = 0;

				if (ctx->Dr7 & 1) {
					v11 = 1;
				}

				if (ctx->Dr7 & 4) {
					v10 = 1;
				}

				if (ctx->Dr7 & 0x10) {
					v9 = 1;
				}

				v2 = ctx->Dr7 & 0x40;
				if (v2) {
					v8 = 1;
				}

				if (v11) {
					if (v10) {
						if (v9) {
							v3 = v8;
							if (v8) {
								return;
							}
							ctx->Dr3 = addr;
							v8 = 1;
							v7 = 3;
						}
						else {
							ctx->Dr2 = addr;
							v9 = 1;
							v7 = 2;
						}
					}
					else {
						ctx->Dr1 = addr;
						v10 = 1;
						v7 = 1;
					}
				}
				else {
					ctx->Dr0 = addr;
					v11 = 1;
					v7 = 0;
				}
				ctx->Dr6 = 0;
				v6 = 0;
				v5 = 0;

				unk_sub_1002F5E0(&ctx->Dr7, 4 * v7 + 16, 2, 0);
				unk_sub_1002F5E0(&ctx->Dr7, 4 * v7 + 18, 2, v5);
				v3 = unk_sub_1002F5E0(&ctx->Dr7, 2 * v7, 1, 1);
#			endif
		}

		long __stdcall complete_trap(LPEXCEPTION_POINTERS inf) {
			static DWORD stored_context_record = 0;

#			if !defined(_WIN64)
				if (inf->ExceptionRecord->ExceptionCode == 0x80000004) {
					if (inf->ContextRecord->Eip == stored_context_record) {
						inf->ContextRecord->Esp -= 4;
						DEREF_PTR_AS(DWORD, inf->ContextRecord->Esp) = inf->ContextRecord->Eip;
						inf->ContextRecord->Eip = unk_addr_store;
						disable_hardware_breakpoints(inf->ContextRecord);
						stored_context_record = 0;
						return EXCEPTION_CONTINUE_EXECUTION;
					}
					else if (DEREF_PTR_AS(BYTE, inf->ContextRecord->Eip) != 0x83 || DEREF_PTR_AS(BYTE, inf->ContextRecord->Eip + 1) != 0xC4) {
						return EXCEPTION_CONTINUE_SEARCH;
					}
					else {
						stored_context_record = DEREF_PTR_AS(DWORD, inf->ContextRecord->Ebp + 4);
						disable_hardware_breakpoints(inf->ContextRecord);
						assign_hardware_breakpoint(inf->ContextRecord, stored_context_record);
						return EXCEPTION_CONTINUE_EXECUTION;
					}
				}
				else if (inf->ExceptionRecord->ExceptionCode == 0x40101010) {
					assign_hardware_breakpoint(inf->ContextRecord, inf->ExceptionRecord->ExceptionInformation[0]);
					return EXCEPTION_CONTINUE_EXECUTION;
				}
#			endif

			return EXCEPTION_CONTINUE_SEARCH;
		}

		void __stdcall raise_exception(ULONG_PTR arguments) {
			RaiseException(0x40101010, 0, 1, &arguments);
		}

		void ceg_zone_loc(void* zone_mem_loc) {
			LOG("Component/CEG", DEBUG, "zone loc: {}", and_rel(PTR_AS(std::uintptr_t, zone_mem_loc)));
		}

		void ceg_hook_stub(void* arg) {
			ceg_zone_loc(arg);
			memmove(zone_file_mem_buf, arg, 0x10);
			memcpy_og(zone_file_mem, zone_file_mem_buf);
			unk_addr_store = reinterpret_cast<std::uintptr_t>(zone_file_mem);
			raise_exception(reinterpret_cast<ULONG_PTR>(arg));
		}

		void memcpy_stub(void* place, const void* data, std::size_t length) {
			DWORD old_protect{};
			VirtualProtect(place, length, PAGE_EXECUTE_READWRITE, &old_protect);

			memcpy(place, data, length);

			VirtualProtect(place, length, old_protect, &old_protect);
			FlushInstructionCache(GetCurrentProcess(), place, length);
		}
	}

	struct component final : generic_component {
		void post_load() override {
			auto ceg_memcpy_res = memory::sig_scan({}, "E8 ? ? ? ? 8B 56 08 8B 46 0C 8B 4E 04");
			ceg_memcpy_res.sub(0x2E).apply(&memcpy_og);
			utils::hook::call(ceg_memcpy_res.get(), memcpy_stub);

			// most definitely not working on sp, doesnt even match the binary, should work on mp and zm though.
			if (identification::game::get_version().mode_ != identification::game::mode::SP) {
				utils::hook::call(memory::sig_scan({}, "8B 44 24 18 8B 4C 24 14 50 51 53").as<std::uintptr_t>() + 0x0D, memory::sig_scan({}, "C7 86 80 00 00 00 00 01 00 00").as<std::uintptr_t>() - 0x5F);
			}

			utils::hook::set<std::uint8_t>(memory::sig_scan({}, "56 8B F1 83 7E 08 00 74 4B 8B 46 04").get(), 0xC3);

			utils::hook::set<std::uint8_t>(memory::sig_scan({}, "55 8B EC 8B 45 08 83 38 00 75 04").get(), 0xC3);
			AddVectoredExceptionHandler(1, complete_trap);
			
			utils::hook::set<std::uint8_t>(memory::sig_scan({}, "83 EC 48 53 55 56 57 6A 01 8D 44 24 34 50 FF 15").get(), 0xC3);
			utils::hook::set<std::uint8_t>(memory::sig_scan({}, "83 EC 48 53 55 56 57 6A 01 8D 44 24 34 50 33 ED").get(), 0xC3);

			utils::hook::nop(memory::sig_scan({}, "68 ? ? ? ? FF 15 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? C6 05").get(), 9);

			if (identification::game::is(identification::game::version::t6::v1_0_44_1759941_MP)) {
				std::vector<std::uintptr_t> ceg_hook_stub_locations = {
					0x405BB6, 0x43C95F, 0x4C7BB1, 0x4D473F, 0x4ED447, 0x4FECF6, 0x50490F, 0x510CE6, 0x564DE6, 0x5FD8E7, 0x680461,
					0x6B80A1, 0x6D3526, 0x6F2D8F
				};

				for (auto& loc : ceg_hook_stub_locations) {
					utils::hook::call(loc, ceg_hook_stub);
				}

				std::map<std::uintptr_t, std::uintptr_t> patched_function_ptrs = {
					{ 0x41FCA0, 0x4A1620 },
					{ 0x461F20, 0x5B8620 },
					{ 0x492FF0, 0x980220 },
					{ 0x49C6C0, 0x7CF040 },
					{ 0x4AE6F0, 0x6A1DB0 },
					{ 0x4D8CE0, 0x608A20 },
					{ 0x4E35D0, 0x419C30 },
					{ 0x581E50, 0x5D2E90 },
					{ 0x592AE0, 0x7CC060 },
					{ 0x5EAF70, 0x59DEC0 },
					{ 0x6348A0, 0x5EE560 },
					{ 0x680110, 0x97B2F0 },
					{ 0x4AB110, 0x7D0100 },
					{ 0x47D650, 0x1050D20 },
					{ 0x634B00, 0x25 },
					{ 0x6D77E0, 0x60 },
					{ 0x49D370, 0x11 },
					{ 0x4C0970, 0x3F },
					{ 0x68DCE0, 5 },
					{ 0x69EC80, 0x7D },
					{ 0x40A260, 0x11 },
					{ 0x6173E0, 0x1D },
					{ 0x57C050, 0x22 },
					{ 0x4F2460, 0x74 },
					{ 0x690210, 0xEDB88320 },
					{ 0x4D32D0, 0xEDB88320 },
					{ 0x6AC3A0, 0xEDB88320 },
					{ 0x49C8B0, 0xEDB88320 },
					{ 0x589870, 0xEDB88320 },
					{ 0x573980, 0x340BAE8 },
					{ 0x59F560, 0x340BB08 },
					{ 0x4F2A90, 0x340B8A8 },
					{ 0x6AC750, 0x340B8B8 },
					{ 0x609690, 0x340BD90 },
					{ 0x616DD0, 0x340BDB0 },
					{ 0x628AF0, 0x340BB68 },
					{ 0x635170, 0x340BBA4 },
					{ 0x642C00, 0x340B938 },
					{ 0x59B590, 0x340B958 },
					{ 0x4B18F0, 0x340BE00 },
					{ 0x675E80, 0x340BDE0 },
					{ 0x47D650, 0x1050D20 },
					{ 0x4D88C0, 0x1050D20 },
					{ 0x666000, 0x1050D20 },
					{ 0x4138C0, 0x1050D20 },
					{ 0x50C2E0, 0x1050D1C }
				};

				for (auto& [og, new_ptr] : patched_function_ptrs) {
					// exec a mov
					DEREF_PTR_AS(BYTE, og) = 0xB8;
					DEREF_PTR_AS(std::uintptr_t, og + 1) = new_ptr;
				}

				utils::hook::call(0x415BF7, 0x4B53F0);
				utils::hook::jump(0x5D9BCA, 0x5F6300);
				utils::hook::call(0x66B2EF, 0x6B0360);
				utils::hook::jump(0x522610, 0x44B290);
				utils::hook::call(0x703247, 0x530E70);
				utils::hook::call(0x5FE5E0, 1 - 1); // 1 - 1 yep it doesnt work if i just do 0 THANK YOU MICROSOCFT
			}

			std::vector<ceg_sig_replace> sig_replaces = {
				{ "? ? E8 ? ? ? ? 8A 44 24 23", 7, "B0 01 90 90" },
				{ "50 C6 ? ? ? ? E8 ? ? ? ? 83 C4 ? C3", 6, "B0 01 90 90 90" },
				{ "50 C7 44 24 ? ? 00 00 00 E8 ? ? ? ? 83 C4 ? C3", 10, "B0 01 90 90 90" },
				{ "50 C7 44 24 ? ? 00 00 00 C7 ? ? ? ? ? ? ? E8 ? ? ? ? 83 C4 ? C3", 17, "B0 01 90 90 90" },
				{ "50 C6 ? ? ? E8 ? ? ? ? 83 C4 ? 64", 5, "B0 01 90 90 90" },
				{ "50 C7 45 ? ? 00 00 00 E8 ? ? ? ? 83 C4 ? 64", 9, "B0 01 90 90 90" },
				{ "50 C7 45 ? ? 00 00 00 C7 ? ? ? ? ? ? E8 ? ? ? ? 83 C4 ? C3", 15, "B0 01 90 90 90" },
				{ "56 E8 ? ? ? ? 8B F0 E8 ? ? ? ? 50 56 E8", 0, "B0 01 C3" },
				{ "E8 ? ? ? ? 84 C0 5E 68 ? ? 00 00 6A 03", 0, "33 C0 90 90 90" },
				{ "E8 ? ? ? ? 84 C0 5E 6A ? 6A 03", 0, "33 C0 90 90 90" },
				{ "80 7C 24 04 00 75 ? 56 8B", 0, "B0 01 C3" },
				{ "8D 45 08 83 E8 04 89 45 F8 8B", -9, "E6" },
				{ "81 EC 00 08 00 00 68 ? ? ? 00 E8 ? ? ? ?", 0, "E6" },
				{ "0B C1 74 0B 84 DB 74 07 B8 01 00 00 00 5B C3 33", 15, "B0 01" },
				{ "83 EC 14 53 55 56 57 E8 ? ? ? ? E8 ? ? ? ?", 0, "C3" },
				{ "81 EC 24 04 00 00 8B 84 24 2C 04 00 00 8B C8 2B", 0, "C3" },
				{ "55 8B EC 51 68 ? ? ? 00 68 ? ? ? 00 64 FF 35 00 00 00 00 64", 0, "C3" },
				{ "55 8B EC 83 EC ? 68 ? ? ? 00 68 ? ? ? 00 64 FF", 0, "C3" },
				{ "5F 5E 5D B0 01 5B 81 C4 74 02 00 00 C3", 8, "78" },
				{ "57 8B 4C 24 08 8B 7C 24 0C 33 C0 89 08 5F C3", 0, "C3" },
				{ "81 EC 74 02 00 00 8B 8C 24 80 02 00 00 53 55 56", 0, "B0 01 C3" },
				{ "51 8D 04 24 6A ? 50 C7 44 24 08 ?", 0, "B0 01 C3" },
				//{ "55 8B EC 81 EC ? ? 00 00 53 56 57 8B 3D", 0, "C3" },
				//{ "51 8D 04 24 6A 3F 50 C7 44 24 08 3F", 0, "C3" },
				//{ "75 44 56 8B 74 24 0C", 0, "71" },
				//{ "51 8D 44 24 ? 50 E8 ? ? ? ? 83 C4 ? C3", 0, "C3" },
				//{ "83 EC 48 53 55 56 57 6A 01 8D 44 24 34", 0, "C3" },
			};

			std::size_t successful_replaces = 0;
			for (auto& replace : sig_replaces) {
				if (replace.patch()) {
					successful_replaces++;
				}
			}

			LOG("Component/CEG", INFO, "{} of {} replacement patches successful.", successful_replaces, sig_replaces.size());
		}
	};
}

REGISTER_COMPONENT(ceg::component)