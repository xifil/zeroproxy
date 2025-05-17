#include "common.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <utils/hook.hpp>

/*
 * this is not a copy and pasted client
 * (thank you serious)
 */

namespace anticheat {
	namespace {
		utils::hook::detour nt_query_information_thread_hook;
		utils::hook::detour nt_query_system_information_hook;
		utils::hook::detour nt_set_information_thread_hook;
		utils::hook::detour virtual_alloc_hook;

		NTSTATUS nt_query_information_thread_stub(HANDLE thread_handle, std::uint32_t thread_information_class, PVOID thread_information,
			ULONG thread_information_length, PULONG return_length)
		{
			// ThreadHideFromDebugger
			if (thread_information_class == 0x11) {
				if (thread_information_length != 1) {
					return -1;
				}

				DEREF_PTR_AS(std::uint8_t, thread_information) = 1;
				return 0;
			}

			return nt_query_information_thread_hook.invoke<NTSTATUS>(thread_handle, thread_information_class, thread_information, thread_information_length,
				return_length);
		}

		NTSTATUS nt_query_system_information_stub(const SYSTEM_INFORMATION_CLASS system_information_class, const PVOID system_information,
			const ULONG system_information_length, const PULONG return_length)
		{
			void* faulting_module;
			RtlPcToFileHeader(_ReturnAddress(), &faulting_module);

			if (faulting_module != nullptr && faulting_module == PTR_AS(void*, 0_b)) {
				/*
				 * Number 16, "while true":
				 * 
				 * the first thing you'd want to do in your code is "while true".
				 * this will make the code unresponsive, and not work :moyai:
				 */
				LOG("Component/Anticheat", INFO, "Anticheat query blocked.");
				while (true) {
					Sleep(100000);
				}
			}

			return nt_query_system_information_hook.invoke<NTSTATUS>(system_information_class, system_information, system_information_length, return_length);
		}
		
		NTSTATUS nt_set_information_thread_stub(HANDLE thread_handle, THREAD_INFORMATION_CLASS thread_information_class, PVOID thread_information,
			ULONG thread_information_length)
		{
			// ThreadHideFromDebugger
			if (thread_information_class == 0x11) {
				if (thread_information_length) {
					return -1;
				}

				if (PTR_AS(std::int64_t, thread_handle) != -2) {
					return -1;
				}

				return 0;
			}

			return nt_set_information_thread_hook.invoke<NTSTATUS>(thread_handle, thread_information_class, thread_information, thread_information_length);
		}

		LPVOID virtual_alloc_stub(LPVOID lp_address, std::size_t dw_size, DWORD fl_allocation_type, DWORD fl_protect) {
			auto return_address = PTR_AS(std::uintptr_t, _ReturnAddress());
			if (return_address == 0x225920D_b /* tls callback */ || return_address == 0x23C583B_b /* memory initializer */
				|| return_address == 0x2269D9D_b /* anticheat 2.1 */ || return_address == 0x22A05D2_b /* anticheat 2.2 */)
			{
				LOG("Component/Anticheat", INFO, "VirtualAlloc hook succeeded at {}.", and_rel(return_address));
				return PTR_AS(void*, PTR_AS(std::uintptr_t, GetModuleHandleA("ntdll.dll")) + 0x1000);
			}

			return virtual_alloc_hook.invoke<LPVOID>(lp_address, dw_size, fl_allocation_type, fl_protect);
		}

		void ac_return_stub() {
			// do nothing
		}
	}

	struct component final : generic_component {
		component_priority priority() const override {
			/*
			 * is this arxan? no, arxan doesn't exist in this land. however, I want to initialise this early so we're using
			 * arxan's priority
			 */
			return component_priority::arxan;
		}

		void post_load() override {
			nt_query_information_thread_hook.create("ntdll.dll", "NtQueryInformationThread", nt_query_information_thread_stub);
			nt_query_system_information_hook.create("ntdll.dll", "NtQuerySystemInformation", nt_query_system_information_stub);
			nt_set_information_thread_hook.create("ntdll.dll", "NtSetInformationThread", nt_set_information_thread_stub);
			virtual_alloc_hook.create("kernelbase.dll", "VirtualAlloc", virtual_alloc_stub);

			/* anticheat intitializer constants */
			utils::hook::set<std::uint64_t>(0x8E57400_b, 0x7331D36860FF300D);
			utils::hook::set<std::uint64_t>(0x8E57408_b, 0xD092BEA64EC3D509);
			utils::hook::set<std::uint64_t>(0x8E573A8_b, 0xFD802801C8DEB7BD);

			/* patch ac threads (ft. on dll load) */
			utils::hook::jump(0x736E0_b, ac_return_stub);		// ac_unk7
			utils::hook::jump(0x77B60_b, ac_return_stub);		// ac_unk10
			utils::hook::jump(0x7BBF0_b, ac_return_stub);		// ac_unk11
			utils::hook::jump(0x22C7FE0_b, ac_return_stub);		// ac_unk13_threaded
			utils::hook::jump(0x22F04C0_b, ac_return_stub);		// ac_unk8
			utils::hook::jump(0x22628C0_b, ac_return_stub);		// ac_unk2_threaded
			utils::hook::jump(0x2263AC0_b, ac_return_stub);		// ac_on_dll_load

			/* skip copying data into ntdll */
			utils::hook::set<std::uint8_t>(0x22595C4_b, 0xEB);	// tls callback
			utils::hook::set<std::uint8_t>(0x23C5C01_b, 0xEB);	// memory init
			utils::hook::set<std::uint8_t>(0x226A15C_b, 0xEB);	// anticheat 2.1
			utils::hook::set<std::uint8_t>(0x22A09E9_b, 0xEB);	// anticheat 2.2

			/* patch setting thread info (anti-debug) */
			std::uint8_t xor_rax_rax[] = { 0x48, 0x31, 0xC0 };
			std::uint8_t xor_eax_eax[] = { 0x31, 0xC0 };
			utils::hook::copy(0x225B381_b, xor_rax_rax, ARRAYSIZE(xor_rax_rax));
			utils::hook::copy(0x226B921_b, xor_eax_eax, ARRAYSIZE(xor_eax_eax));
			utils::hook::copy(0x23D3326_b, xor_rax_rax, ARRAYSIZE(xor_rax_rax));

			/* CreateRemoteThread check (@ 0x14225A173) */
			std::uint8_t nop_jmp[] = { 0x90, 0xE9 };
			utils::hook::nop(0x22598FA_b, 2);
			utils::hook::nop(0x2259904_b, 2);
			utils::hook::copy(0x225990F_b, nop_jmp, ARRAYSIZE(nop_jmp));

			/* prevent the game from exiting */
			utils::hook::nop(0x23F120E_b, 2);
			utils::hook::nop(0x23F1217_b, 2);
			utils::hook::nop(0x23F1232_b, 2);
			utils::hook::nop(0x23F0FC0_b, 6);
			utils::hook::nop(0x23F0D6A_b, 6);

			utils::hook::copy(0x23F123F_b, nop_jmp, ARRAYSIZE(nop_jmp));
			FlushInstructionCache(GetCurrentProcess(), PTR_AS(void*, 0x23F123F_b), ARRAYSIZE(nop_jmp));

			/* patch CheckRemoteDebuggerPresent */
			std::uint8_t xor_rax_rax_nop[] = { 0x48, 0x31, 0xC0, 0x90 };
			utils::hook::nop(0x2282470_b, 6);
			utils::hook::copy(0x2282470_b, xor_rax_rax_nop, ARRAYSIZE(xor_rax_rax_nop));
			FlushInstructionCache(GetCurrentProcess(), PTR_AS(void*, 0x2282470_b), 1);

			/* remove mutex checks (allow multi-instancing) */
			utils::hook::nop(0x226D85A_b, 6);
			utils::hook::nop(0x226CF83_b, 2);
			utils::hook::nop(0x226E40F_b, 6);
			utils::hook::nop(0x226DE83_b, 2);
		}
	};
}

REGISTER_COMPONENT(anticheat::component)