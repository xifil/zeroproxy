#include "common.hpp"
#include "component/call_spoofer.hpp"
#include "game/game.hpp"

#include <loader/component_loader.hpp>
#include <memory/memory.hpp>
#include <utils/hook.hpp>

/*
 * this is not a copy and pasted client
 * (thank you serious)
 */

namespace anticheat {
	namespace {
		utils::hook::detour unk_ac_unk3_hook;
		utils::hook::detour unk_ac_unk4_hook;
		utils::hook::detour unk_ac_unk5_hook;
		utils::hook::detour unk_ac_unk6_hook;
		utils::hook::detour nt_query_information_thread_hook;
		utils::hook::detour nt_query_system_information_hook;
		utils::hook::detour nt_set_information_thread_hook;
		utils::hook::detour virtual_alloc_hook;

		std::uint64_t ac_generic_hook(std::function<std::uint64_t()> callback) {
			std::uint64_t stored_state = *game::unk_AC_State;
			std::uint64_t res = callback();
			*game::unk_AC_State = stored_state;
			return res;
		}

		std::uint64_t unk_ac_unk3_stub(std::uint64_t a1, std::uint64_t a2) {
			return ac_generic_hook([a1, a2]() {
				return call_spoofer::spoof_hook_invoke<std::uint64_t>(unk_ac_unk3_hook, a1, a2);
			});
		}

		std::uint64_t unk_ac_unk4_stub(std::uint64_t a1) {
			return ac_generic_hook([a1]() {
				return call_spoofer::spoof_hook_invoke<std::uint64_t>(unk_ac_unk4_hook, a1);
			});
		}

		std::uint64_t unk_ac_unk5_stub(std::uint64_t a1) {
			return ac_generic_hook([a1]() {
				return call_spoofer::spoof_hook_invoke<std::uint64_t>(unk_ac_unk5_hook, a1);
			});
		}

		std::uint64_t unk_ac_unk6_stub(std::uint64_t a1) {
			return ac_generic_hook([a1]() {
				return call_spoofer::spoof_hook_invoke<std::uint64_t>(unk_ac_unk6_hook, a1);
			});
		}

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

			static utils::nt::library game{};

			static auto ra_tls_callback = memory::sig_scan(game, "48 89 05 ? ? ? ? 48 8B D0 48 85 C0 0F 85 ? ? ? ? 49 BD").as<std::uintptr_t>();
			static auto ra_memory_init = memory::sig_scan(game, "48 89 05 ? ? ? ? 48 8B D0 48 85 C0 0F 85 ? ? ? ? 48 83 C3").as<std::uintptr_t>();
			static auto ra_anticheat_2_1 = memory::sig_scan(game, "48 8B D0 48 89 05 ? ? ? ? 48 85 C0").as<std::uintptr_t>();
			static auto ra_anticheat_2_2 = memory::sig_scan(game, "48 8B C8 48 89 05 ? ? ? ? 48 85 C0 0F 85").as<std::uintptr_t>();

			if (return_address == ra_tls_callback || return_address == ra_memory_init || return_address == ra_anticheat_2_1
				|| return_address == ra_anticheat_2_2)
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
			utils::nt::library game{};

			unk_ac_unk3_hook.create(game::unk_AC_Unk3, unk_ac_unk3_stub);
			unk_ac_unk4_hook.create(game::unk_AC_Unk4, unk_ac_unk4_stub);
			unk_ac_unk5_hook.create(game::unk_AC_Unk5, unk_ac_unk5_stub);
			unk_ac_unk6_hook.create(game::unk_AC_Unk6, unk_ac_unk6_stub);
			nt_query_information_thread_hook.create("ntdll.dll", "NtQueryInformationThread", nt_query_information_thread_stub);
			nt_query_system_information_hook.create("ntdll.dll", "NtQuerySystemInformation", nt_query_system_information_stub);
			nt_set_information_thread_hook.create("ntdll.dll", "NtSetInformationThread", nt_set_information_thread_stub);
			virtual_alloc_hook.create("kernelbase.dll", "VirtualAlloc", virtual_alloc_stub);

			/* anticheat intitializer constants */
			utils::hook::set<std::uint64_t>(memory::sig_scan(game, "48 89 05 ? ? ? ? 48 8B 8D").add(3).rip().get(), 0x7331D36860FF300D);
			utils::hook::set<std::uint64_t>(memory::sig_scan(game, "48 33 0D ? ? ? ? 48 BA").add(3).rip().get(), 0xD092BEA64EC3D509);
			utils::hook::set<std::uint64_t>(memory::sig_scan(game, "48 89 05 ? ? ? ? 8B 44 24 ? 49 BF").add(3).rip().get(), 0xFD802801C8DEB7BD);

			/* patch ac threads (ft. on dll load) */
			utils::hook::jump(game::unk_AC_OnDllLoaded, ac_return_stub);
			utils::hook::jump(game::unk_AC_Unk2_Threaded, ac_return_stub);
			utils::hook::jump(game::unk_AC_Unk7, ac_return_stub);
			utils::hook::jump(game::unk_AC_Unk8, ac_return_stub);
			utils::hook::jump(game::unk_AC_Unk10, ac_return_stub);
			utils::hook::jump(game::unk_AC_Unk11, ac_return_stub);
			utils::hook::jump(game::unk_AC_Unk13_Threaded, ac_return_stub);

			/* skip copying data into ntdll */
			utils::hook::set<std::uint8_t>(memory::sig_scan(game, "74 ? 48 85 C9 74 ? 4C 3B C2").get(), 0xEB);						// tls callback
			utils::hook::set<std::uint8_t>(memory::sig_scan(game, "74 ? 48 85 C9 74 ? 4C 3B C0").get(), 0xEB);						// memory init
			utils::hook::set<std::uint8_t>(memory::sig_scan(game, "74 ? 48 85 C9 74 ? 48 3B F8").get(), 0xEB);						// anticheat 2.1
			utils::hook::set<std::uint8_t>(memory::sig_scan(game, "0F 84 ? ? ? ? 48 85 D2 0F 84 ? ? ? ? 48 3B F8").get(), 0xEB);	// anticheat 2.2

			/* patch setting thread info (anti-debug) */
			std::uint8_t xor_rax_rax[] = { 0x48, 0x31, 0xC0 };
			utils::hook::copy(memory::sig_scan(game, "41 FF D2 85 C0 0F 88 ? ? ? ? 48 8B 0D ? ? ? ? 48 85 C9").get(), xor_rax_rax, ARRAYSIZE(xor_rax_rax));
			utils::hook::copy(memory::sig_scan(game, "41 FF D2 85 C0 0F 88 ? ? ? ? 48 8B 0D ? ? ? ? 49 BC").get(), xor_rax_rax, ARRAYSIZE(xor_rax_rax));

			std::uint8_t xor_eax_eax[] = { 0x31, 0xC0 };
			utils::hook::copy(memory::sig_scan(game, "FF D0 85 C0 0F 88 ? ? ? ? 48 BB").get(), xor_eax_eax, ARRAYSIZE(xor_eax_eax));

			/* CreateRemoteThread check (@ 0x14225A173) */
			std::uint8_t nop_jmp[] = { 0x90, 0xE9 };
			utils::hook::nop(memory::sig_scan(game, "74 ? 8B 11 49 03 D1 48 3B DA 72 ? 8B 41 ? 48 03 C2 48 3B D8 0F 86 ? ? ? ? 48 83 C1 ? 4D 85 C0 75 ? 4D 8B"
				" 12 4D 3B D3 75 ? E9").get(), 2);
			utils::hook::nop(memory::sig_scan(game, "72 ? 8B 41 ? 48 03 C2 48 3B D8 0F 86 ? ? ? ? 48 83 C1 ? 4D 85 C0 75 ? 4D 8B 12 4D 3B D3 75 ? E9").get(), 2);
			utils::hook::copy(memory::sig_scan(game, "0F 86 ? ? ? ? 48 83 C1 ? 4D 85 C0 75 ? 4D 8B 12 4D 3B D3 75 ? E9").get(), nop_jmp, ARRAYSIZE(nop_jmp));

			/* prevent the game from exiting */
			utils::hook::nop(memory::sig_scan(game, "77 ? 4C 39 2D").get(), 2);
			utils::hook::nop(memory::sig_scan(game, "77 ? 48 8B 53 ? 4C 89 2D").get(), 2);
			utils::hook::nop(memory::sig_scan(game, "77 ? 49 2B C5").get(), 2);
			utils::hook::nop(memory::sig_scan(game, "0F 85 ? ? ? ? 4C 8B 0D ? ? ? ? 4C 8B 2B").get(), 6);
			utils::hook::nop(memory::sig_scan(game, "0F 84 ? ? ? ? 4C 8B 0D ? ? ? ? 4C 8B 6B").get(), 6);

			auto exit_jbe_tmp = memory::sig_scan(game, "0F 86 ? ? ? ? 4C 8B AC 24").get();
			utils::hook::copy(exit_jbe_tmp, nop_jmp, ARRAYSIZE(nop_jmp));
			FlushInstructionCache(GetCurrentProcess(), PTR_AS(void*, exit_jbe_tmp), ARRAYSIZE(nop_jmp));

			/* patch CheckRemoteDebuggerPresent */
			auto crdp_check_tmp = memory::sig_scan(game, "8B 85 ? ? ? ? 33 DB 83 F8").get();
			std::uint8_t xor_rax_rax_nop[] = { 0x48, 0x31, 0xC0, 0x90 };
			utils::hook::nop(crdp_check_tmp, 6);
			utils::hook::copy(crdp_check_tmp, xor_rax_rax_nop, ARRAYSIZE(xor_rax_rax_nop));
			FlushInstructionCache(GetCurrentProcess(), PTR_AS(void*, crdp_check_tmp), 1);

			/* remove mutex checks (allow multi-instancing) */
			utils::hook::nop(memory::sig_scan(game, "0F 84 ? ? ? ? B8 ? ? ? ? B9 ? ? ? ? 0F B6 95").get(), 6);
			utils::hook::nop(memory::sig_scan(game, "FF D7 90 48 8D BD ? ? ? ? 8D 4B ? 48 83 F8 ? 0F 84 ? ? ? ? 33 C0 F3 AA 48 BF").get(), 2);
			utils::hook::nop(memory::sig_scan(game, "0F 84 ? ? ? ? 48 B9 ? ? ? ? ? ? ? ? 48 8B 05").get(), 6);
			utils::hook::nop(memory::sig_scan(game, "FF D7 90 48 8D BD ? ? ? ? 8D 4B ? 48 83 F8 ? 0F 84 ? ? ? ? 33 C0 F3 AA 48 8B 0D").get(), 2);
		}
	};
}

REGISTER_COMPONENT(anticheat::component)