#pragma once
#include "scylla/scylla_common.hpp"

#include "scylla/pe_file_section.hpp"
#include "scylla/pe_section.hpp"

namespace scylla {
	class pe_parser {
	public:
		pe_parser(const wchar_t* file, bool read_section_headers = true);
		pe_parser(const std::uintptr_t module_base, bool read_section_headers = true);

		~pe_parser();

		bool is_valid_pe_file();
		bool is_pe_64();
		bool is_pe_32();

		bool is_target_file_same_pe_format();

		std::uint16_t get_number_of_sections();
		std::vector<pe_file_section>& get_section_header_list();

		bool has_export_directory();
		bool has_tls_directory();
		bool has_relocation_directory();
		bool has_overlay_data();

		std::uint32_t get_entry_point();

		bool get_section_name_unicode(const int section_index, wchar_t* output, const int output_len);

		std::uint32_t get_section_header_based_file_size();
		std::uint32_t get_section_header_based_size_of_image();

		bool read_pe_sections_from_process();
		bool read_pe_sections_from_file();
		bool save_pe_file_to_disk(const wchar_t* new_file);
		void remove_dos_stub();
		void align_all_section_headers();
		void fix_pe_header();
		void set_default_file_alignment();
		bool dump_process(std::uintptr_t mod_base, std::uintptr_t entry_point, const wchar_t* dump_file_path);
		bool dump_process(std::uintptr_t mod_base, std::uintptr_t entry_point, const wchar_t* dump_file_path, std::vector<pe_section>& section_list);

		void set_entry_point_va(std::uintptr_t entry_point);
		void set_entry_point_rva(std::uint32_t entry_point);

		static bool update_pe_header_checksum(const wchar_t* target_file, std::uint32_t file_size);
		std::uint8_t* get_section_memory_by_index(int index);
		std::uint32_t get_section_memory_size_by_index(int index);
		int convert_rva_to_offset_vector_index(std::uintptr_t dw_rva);
		std::uintptr_t convert_offset_to_rva_vector(std::uintptr_t dw_offset);
		std::uintptr_t convert_rva_to_offset_vector(std::uintptr_t dw_rva);
		std::uintptr_t convert_rva_to_offset_relative(std::uintptr_t dw_rva);
		std::uint32_t get_section_address_rva_by_index(int index);

		PIMAGE_NT_HEADERS get_current_nt_header();
	protected:
		pe_parser();

		static const std::uint32_t file_alignment_constant = 0x200;

		const wchar_t* filename_;
		std::uintptr_t module_base_address_;

		/************************************************************************/
		/* PE FILE                                                              */
		/*                                                                      */
		/*  IMAGE_DOS_HEADER      64   0x40                                     */
		/*	IMAGE_NT_HEADERS32   248   0xF8                                     */
		/*	IMAGE_NT_HEADERS64   264  0x108                                     */
		/*	IMAGE_SECTION_HEADER  40   0x28                                     */
		/************************************************************************/

		PIMAGE_DOS_HEADER p_dos_header_;
		std::uint8_t* p_dos_stub_; // between dos header and section header
		std::uint32_t dos_stub_size_;
		PIMAGE_NT_HEADERS32 p_nt_header32_;
		PIMAGE_NT_HEADERS64 p_nt_header64_;
		std::vector<pe_file_section> list_pe_section_;
		std::uint8_t* overlay_data_;
		std::uint32_t overlay_size_;
		/************************************************************************/

		std::uint8_t* file_memory_;
		std::uint8_t* header_memory_;

		HANDLE h_file_;
		std::uint32_t file_size_;

		bool read_pe_header_from_file(bool read_section_headers);
		bool read_pe_header_from_process(bool read_section_headers);

		bool has_directory(const int directory_index);
		bool get_section_headers();
		void get_dos_and_nt_header(std::uint8_t* memory, LONG size);
		std::uint32_t calc_correct_pe_header_size(bool read_section_headers);
		std::uint32_t get_initial_header_read_size(bool read_section_headers);
		bool open_file_handle();
		void close_file_handle();
		void init_class();

		std::uint32_t is_memory_not_null(std::uint8_t* data, int data_size);
		bool open_write_file_handle(const wchar_t* new_file);
		bool write_zero_memory_to_file(HANDLE hFile, std::uint32_t file_offset, std::uint32_t size);

		bool read_pe_section_from_file(std::uint32_t read_offset, pe_file_section& section);
		bool read_pe_section_from_process(std::uintptr_t read_offset, pe_file_section& section);

		bool read_section_from_process(const std::uintptr_t read_offset, pe_file_section& section);
		bool read_section_from_file(const std::uint32_t read_offset, pe_file_section& section);
		bool read_section_from(const std::uintptr_t read_offset, pe_file_section& section, const bool is_process);

		std::uintptr_t get_standard_image_base();

		bool add_new_last_section(const char* section_name, std::uint32_t section_size, std::uint8_t* section_data);
		std::uint32_t align_value(std::uint32_t bad_value, std::uint32_t align_to);

		void set_number_of_sections(std::uint16_t number_of_sections);

		void remove_iat_directory();
		bool get_file_overlay();
	};
}
