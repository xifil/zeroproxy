#pragma once
#include "common_core.hpp"
#include "nt/activation_context_data.hpp"
#include "nt/api_set_namespace.hpp"
#include "nt/assembly_storage_map.hpp"
#include "nt/silo_user_shared_data.hpp"

namespace nt {
#	define GDI_HANDLE_BUFFER_SIZE32 34
#	define GDI_HANDLE_BUFFER_SIZE64 60

#	ifndef _WIN64
#		define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE32
#	else
#		define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE64
#	endif

	typedef unsigned long gdi_handle_buffer[GDI_HANDLE_BUFFER_SIZE];

	class process_environment_block {
	public:
		bool inherited_address_space_;										// 0x0000
		bool read_image_file_exec_options_;									// 0x0001
		bool being_debugged_;												// 0x0002
		union {
			std::uint8_t bit_field_;										// 0x0003
			struct {
				bool image_uses_large_pages_ : 1;							// 0x0003:0
				bool is_protected_process_ : 1;								// 0x0003:1
				bool is_image_dynamically_relocated_ : 1;					// 0x0003:2
				bool skip_patching_user32_forwarders_ : 1;					// 0x0003:3
				bool is_packaged_process_ : 1;								// 0x0003:4
				bool is_app_container_ : 1;									// 0x0003:5
				bool is_protected_process_light_ : 1;						// 0x0003:6
				bool is_long_path_aware_process_ : 1;						// 0x0003:7
			};
		};
		HANDLE mutant_;														// 0x0004
		void* image_base_address_;											// 0x0010
		PPEB_LDR_DATA ldr_;													// 0x0018
		PRTL_USER_PROCESS_PARAMETERS process_parameters_;					// 0x0020
		void* sub_system_data_;												// 0x0028
		void* process_heap_;												// 0x0030
		PRTL_CRITICAL_SECTION fast_peb_lock_;								// 0x0038
		PSLIST_HEADER atl_thunk_slist_ptr_;									// 0x0040
		void* ifeo_key_;													// 0x0048
		union {
			unsigned long cross_process_flags_;								// 0x0050
			struct {
				unsigned long process_in_job_ : 1;							// 0x0050:0
				unsigned long process_initializing_ : 1;					// 0x0050:1
				unsigned long process_using_veh_ : 1;						// 0x0050:2
				unsigned long process_using_vch_ : 1;						// 0x0050:3
				unsigned long process_using_fth_ : 1;						// 0x0050:4
				unsigned long process_previously_throttled_ : 1;			// 0x0050:5
				unsigned long process_currently_throttled_ : 1;				// 0x0050:6
				unsigned long process_images_hot_patched_ : 1;				// 0x0050:7 - REDSTONE5
				unsigned long reserved_bits0_ : 24;							// 0x0051:0
			};
		};
	private:
		char pad_0054[0x0004];												// 0x0054
	public:
		union {
			void* kernel_call_back_table_;									// 0x0058
			void* user_shared_info_ptr_;									// 0x0058
		};
		unsigned long system_reserved_;										// 0x0060
		unsigned long atl_thunk_slist_ptr32_;								// 0x0064
		api_set_namespace* api_set_map_;									// 0x0068
		unsigned long tls_expansion_counter_;								// 0x0070
		void* tls_bitmap_;													// 0x0078
		unsigned long tls_bitmap_bits_[2];									// 0x0080
		void* read_only_shared_memory_base_;								// 0x0088
		silo_user_shared_data* shared_data_;								// 0x0090 - HotpatchInformation
		void** read_only_static_server_data_;								// 0x0098
		void* ansi_code_page_data_;											// 0x00A0 - PCPTABLEINFO
		void* oem_code_page_data_;											// 0x00A8 - PCPTABLEINFO
		void* unicode_case_table_data_;										// 0x00B0 - PNLSTABLEINFO
		unsigned long number_of_processors_;								// 0x00B8
		unsigned long nt_global_flag_;										// 0x00BC
		ULARGE_INTEGER critical_section_timeout_;							// 0x00C0
		SIZE_T heap_segment_reserve_;										// 0x00C8
		SIZE_T heap_segment_commit_;										// 0x00D0
		SIZE_T heap_de_commit_total_free_threshold_;						// 0x00D8
		SIZE_T heap_de_commit_free_block_threshold_;						// 0x00E0
		unsigned long number_of_heaps_;										// 0x00E8
		unsigned long maximum_number_of_heaps_;								// 0x00EC
		void** process_heaps_;												// 0x00F0 - PHEAP
		void* gdi_shared_handle_table_;										// 0x00F8 - PGDI_SHARED_MEMORY
		void* process_starter_helper_;										// 0x0100
		unsigned long gdi_dc_attribute_list_;								// 0x0108
		PRTL_CRITICAL_SECTION loader_lock_;									// 0x0110
		unsigned long os_major_version_;									// 0x0118
		unsigned long os_minor_version_;									// 0x011C
		std::uint16_t os_build_number_;										// 0x0120
		std::uint16_t os_csd_version_;										// 0x0122
		unsigned long os_platform_id_;										// 0x0124
		unsigned long image_subsystem_;										// 0x0128
		unsigned long image_subsystem_major_version_;						// 0x012C
		unsigned long image_subsystem_minor_version_;						// 0x0130
		KAFFINITY active_process_affinity_mask_;							// 0x0138
		gdi_handle_buffer gdi_handle_buffer_;								// 0x0140
		void* post_process_init_routine_;									// 0x0230
		void* tls_expansion_bitmap_;										// 0x0238
		unsigned long tls_expansion_bitmap_bits_[32];						// 0x0240
		unsigned long session_id_;											// 0x02C0
		ULARGE_INTEGER app_compat_flags_;									// 0x02C8
		ULARGE_INTEGER app_compat_flags_user_;								// 0x02D0
		void* shim_data_;													// 0x02D8
		void* app_compat_info_;												// 0x02E0 - APPCOMPAT_EXE_DATA
		UNICODE_STRING csd_version_;										// 0x02E8
		activation_context_data* activation_context_data_;					// 0x02F8
		assembly_storage_map* process_assembly_storage_map_;				// 0x0300
		activation_context_data* system_default_activation_context_data_;	// 0x0308
		assembly_storage_map* system_assembly_storage_map_;					// 0x0310
		SIZE_T minimum_stack_commit_;										// 0x0318
		void* spare_pointers_[2];											// 0x0320 - 19H1 (previously FlsCallback to FlsHighIndex)
		void* patch_loader_data_;											// 0x0330
		void* chpe_v2_process_info_;										// 0x0338 - _CHPEV2_PROCESS_INFO
		unsigned long app_model_feature_state_;								// 0x0340
		unsigned long spare_ulongs_[2];										// 0x0344
		std::uint16_t active_code_page_;									// 0x034C
		std::uint16_t oem_code_page_;										// 0x034E
		std::uint16_t use_case_mapping_;									// 0x0350
		std::uint16_t unused_nls_field_;									// 0x0352
		void* wer_registration_data_;										// 0x0358
		void* wer_ship_assert_ptr_;											// 0x0360
		union {
			void* context_data_;											// 0x0368 - Windows 7
			void* unused_;													// 0x0368 - Windows 10
			void* ec_code_bit_map_;											// 0x0368 - Windows 11
		};
		void* image_header_hash_;											// 0x0370
		union {
			unsigned long tracing_flags_;									// 0x0378
			struct {
				unsigned long heap_tracing_enabled_ : 1;					// 0x0378:0
				unsigned long crit_sec_tracing_enabled_ : 1;				// 0x0378:1
				unsigned long lib_loader_tracing_enabled_ : 1;				// 0x0378:2
				unsigned long spare_tracing_bits_ : 29;						// 0x0378:3
			};
		};
		unsigned long long csr_server_read_only_shared_memory_base_;		// 0x0380
		PRTL_CRITICAL_SECTION tpp_worker_list_lock_;						// 0x0388
		LIST_ENTRY tpp_worker_list_;										// 0x0390
		void* wait_on_address_hash_table_[128];								// 0x03A0
		void* telemetry_coverage_header_;									// 0x07A0 - REDSTONE3
		unsigned long cloud_file_flags_;									// 0x07A8
		unsigned long cloud_file_diag_flags_;								// 0x07AC - REDSTONE4
		char placeholder_compatibility_mode_;								// 0x07B0
		char placeholder_compatibility_mode_reserved_[7];					// 0x07B1
		void* leap_second_data_;											// 0x07B8 - REDSTONE5
		union {
			unsigned long leap_second_flags_;								// 0x07C0
			struct {
				unsigned long sixty_second_enabled_ : 1;					// 0x07C0:0
				unsigned long reserved_ : 31;								// 0x07C0:1
			};
		};
		unsigned long nt_global_flag2_;										// 0x07C4
		unsigned long long extended_feature_disable_mask_;					// 0x07C8 - since WIN11
	};
	CLASS_ASSERT_SZ_64(process_environment_block, 0x07D0);
}
