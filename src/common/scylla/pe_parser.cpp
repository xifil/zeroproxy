#include "scylla/scylla_common.hpp"

#include "scylla/pe_parser.hpp"
#include "scylla/process_access_help.hpp"

namespace scylla {
	namespace {
		bool pe_file_section_sort_by_pointer_to_raw_data(const pe_file_section& d1, const pe_file_section& d2) {
			return d1.section_header_.PointerToRawData < d2.section_header_.PointerToRawData;
		}

		bool pe_file_section_sort_by_virtual_address(const pe_file_section& d1, const pe_file_section& d2) {
			return d1.section_header_.VirtualAddress < d2.section_header_.VirtualAddress;
		}
	}

	pe_parser::pe_parser() {
		this->init_class();
	}

	pe_parser::pe_parser(const wchar_t* file, bool read_section_headers) {
		this->init_class();

		this->filename_ = file;

		if (this->filename_) {
			this->read_pe_header_from_file(read_section_headers);

			if (read_section_headers) {
				if (this->is_valid_pe_file()) {
					this->get_section_headers();
				}
			}
		}
	}

	pe_parser::pe_parser(const std::uintptr_t module_base, bool read_section_headers) {
		this->init_class();

		this->module_base_address_ = module_base;

		if (this->module_base_address_) {
			this->read_pe_header_from_process(read_section_headers);

			if (read_section_headers) {
				if (this->is_valid_pe_file()) {
					this->get_section_headers();
				}
			}
		}
	}

	pe_parser::~pe_parser() {
		if (this->header_memory_) {
			delete[] this->header_memory_;
		}

		if (this->file_memory_) {
			delete[] this->file_memory_;
		}

		for (size_t i = 0; i < this->list_pe_section_.size(); i++) {
			if (this->list_pe_section_[i].data_) {
				delete[] this->list_pe_section_[i].data_;
			}
		}

		this->list_pe_section_.clear();
	}

	void pe_parser::init_class() {
		this->file_memory_ = nullptr;
		this->header_memory_ = nullptr;

		this->p_dos_header_ = nullptr;
		this->p_dos_stub_ = nullptr;
		this->dos_stub_size_ = 0;
		this->p_nt_header32_ = nullptr;
		this->p_nt_header64_ = nullptr;
		this->overlay_data_ = nullptr;
		this->overlay_size_ = 0;

		this->filename_ = nullptr;
		this->file_size_ = 0;
		this->module_base_address_ = NULL;
		this->h_file_ = INVALID_HANDLE_VALUE;
	}

	bool pe_parser::is_valid_pe_file() {
		if (this->p_dos_header_ && this->p_dos_header_->e_magic == IMAGE_DOS_SIGNATURE) {
			if (this->p_nt_header32_ && this->p_nt_header32_->Signature == IMAGE_NT_SIGNATURE) {
				return true;
			}
		}

		return false;
	}

	bool pe_parser::is_pe_64() {
		if (this->is_valid_pe_file()) {
			return this->p_nt_header32_->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC;
		}

		return false;
	}

	bool pe_parser::is_pe_32() {
		if (this->is_valid_pe_file()) {
			return this->p_nt_header32_->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC;
		}

		return false;
	}

	bool pe_parser::is_target_file_same_pe_format() {
#		ifdef _WIN64
			return this->is_pe_64();
#		else
			return this->is_pe_32();
#		endif
	}

	std::uint16_t pe_parser::get_number_of_sections() {
		return this->p_nt_header32_->FileHeader.NumberOfSections;
	}

	std::vector<pe_file_section>& pe_parser::get_section_header_list() {
		return this->list_pe_section_;
	}

	bool pe_parser::has_export_directory() {
		return this->has_directory(IMAGE_DIRECTORY_ENTRY_EXPORT);
	}

	bool pe_parser::has_tls_directory() {
		return this->has_directory(IMAGE_DIRECTORY_ENTRY_TLS);
	}

	bool pe_parser::has_relocation_directory() {
		return this->has_directory(IMAGE_DIRECTORY_ENTRY_BASERELOC);
	}

	bool pe_parser::has_overlay_data() {
		if (!this->filename_ || !this->is_valid_pe_file()) {
			return false;
		}

		DWORD fileSize = (DWORD)process_access_help::get_file_size(this->filename_);
		return (fileSize > this->get_section_header_based_file_size());
	}

	std::uint32_t pe_parser::get_entry_point() {
		if (this->is_pe_32()) {
			return this->p_nt_header32_->OptionalHeader.AddressOfEntryPoint;
		}

		if (this->is_pe_64()) {
			return this->p_nt_header64_->OptionalHeader.AddressOfEntryPoint;
		}

		return NULL;
	}

	bool pe_parser::get_section_name_unicode(const int section_index, wchar_t* output, const int output_len) {
		CHAR section_name[IMAGE_SIZEOF_SHORT_NAME + 1] = { 0 };
		output[0] = 0;
		memcpy(section_name, this->list_pe_section_[section_index].section_header_.Name, IMAGE_SIZEOF_SHORT_NAME); // not null terminated
		return swprintf_s(output, output_len, L"%S", section_name) != -1;
	}

	std::uint32_t pe_parser::get_section_header_based_file_size() {
		std::uint32_t last_raw_offset = 0, last_raw_size = 0;

		//this is needed if the sections aren't sorted by their RawOffset (e.g. Petite)
		for (std::uint16_t i = 0; i < this->get_number_of_sections(); i++) {
			if (this->list_pe_section_[i].section_header_.PointerToRawData + this->list_pe_section_[i].section_header_.SizeOfRawData > last_raw_offset + last_raw_size) {
				last_raw_offset = this->list_pe_section_[i].section_header_.PointerToRawData;
				last_raw_size = this->list_pe_section_[i].section_header_.SizeOfRawData;
			}
		}

		return last_raw_size + last_raw_offset;
	}

	std::uint32_t pe_parser::get_section_header_based_size_of_image() {
		std::uint32_t last_virtual_offset = 0, last_virtual_size = 0;

		//this is needed if the sections aren't sorted by their RawOffset (e.g. Petite)
		for (std::uint16_t i = 0; i < this->get_number_of_sections(); i++) {
			if (this->list_pe_section_[i].section_header_.VirtualAddress + this->list_pe_section_[i].section_header_.Misc.VirtualSize > last_virtual_offset + last_virtual_size) {
				last_virtual_offset = this->list_pe_section_[i].section_header_.VirtualAddress;
				last_virtual_size = this->list_pe_section_[i].section_header_.Misc.VirtualSize;
			}
		}

		return last_virtual_size + last_virtual_offset;
	}

	bool pe_parser::read_pe_sections_from_process() {
		bool ret_value = true;
		DWORD_PTR read_offset = 0;

		this->list_pe_section_.reserve(this->get_number_of_sections());

		for (WORD i = 0; i < this->get_number_of_sections(); i++) {
			read_offset = this->list_pe_section_[i].section_header_.VirtualAddress + this->module_base_address_;

			this->list_pe_section_[i].normal_size_ = this->list_pe_section_[i].section_header_.Misc.VirtualSize;

			if (!this->read_section_from_process(read_offset, this->list_pe_section_[i])) {
				ret_value = false;
			}
		}

		return ret_value;
	}

	bool pe_parser::read_pe_sections_from_file() {
		bool ret_value = true;
		std::uint32_t read_offset = 0;

		this->list_pe_section_.reserve(this->get_number_of_sections());

		if (this->open_file_handle()) {
			for (std::uint16_t i = 0; i < this->get_number_of_sections(); i++) {
				read_offset = this->list_pe_section_[i].section_header_.PointerToRawData;

				this->list_pe_section_[i].normal_size_ = this->list_pe_section_[i].section_header_.SizeOfRawData;

				if (!this->read_section_from_file(read_offset, this->list_pe_section_[i])) {
					ret_value = false;
				}
			}

			this->close_file_handle();
		}
		else {
			ret_value = false;
		}

		return ret_value;
	}

	bool pe_parser::save_pe_file_to_disk(const wchar_t* new_file) {
		bool ret_value = true;
		DWORD dw_file_offset = 0, dw_write_size = 0;

		if (this->get_number_of_sections() != this->list_pe_section_.size()) {
			return false;
		}

		if (this->open_write_file_handle(new_file)) {
			// Dos header
			dw_write_size = sizeof(IMAGE_DOS_HEADER);
			if (!process_access_help::write_memory_to_file(this->h_file_, dw_file_offset, dw_write_size, this->p_dos_header_)) {
				ret_value = false;
			}
			dw_file_offset += dw_write_size;


			if (this->dos_stub_size_ && this->p_dos_stub_) {
				// Dos Stub
				dw_write_size = this->dos_stub_size_;
				if (!process_access_help::write_memory_to_file(this->h_file_, dw_file_offset, dw_write_size, this->p_dos_stub_)) {
					ret_value = false;
				}
				dw_file_offset += dw_write_size;
			}


			// Pe Header
			if (this->is_pe_32()) {
				dw_write_size = sizeof(IMAGE_NT_HEADERS32);
			}
			else {
				dw_write_size = sizeof(IMAGE_NT_HEADERS64);
			}

			if (!process_access_help::write_memory_to_file(this->h_file_, dw_file_offset, dw_write_size, this->p_nt_header32_)) {
				ret_value = false;
			}
			dw_file_offset += dw_write_size;

			// section headers
			dw_write_size = sizeof(IMAGE_SECTION_HEADER);

			for (std::uint16_t i = 0; i < this->get_number_of_sections(); i++) {
				if (!process_access_help::write_memory_to_file(this->h_file_, dw_file_offset, dw_write_size, &this->list_pe_section_[i].section_header_)) {
					ret_value = false;
					break;
				}
				dw_file_offset += dw_write_size;
			}

			for (WORD i = 0; i < this->get_number_of_sections(); i++) {
				if (!this->list_pe_section_[i].section_header_.PointerToRawData) {
					continue;
				}

				if (this->list_pe_section_[i].section_header_.PointerToRawData > dw_file_offset) {
					dw_write_size = this->list_pe_section_[i].section_header_.PointerToRawData - dw_file_offset; //padding

					if (!this->write_zero_memory_to_file(this->h_file_, dw_file_offset, dw_write_size)) {
						ret_value = false;
						break;
					}
					dw_file_offset += dw_write_size;
				}

				dw_write_size = this->list_pe_section_[i].data_size_;

				if (dw_write_size) {
					if (!process_access_help::write_memory_to_file(this->h_file_, this->list_pe_section_[i].section_header_.PointerToRawData, dw_write_size,
						this->list_pe_section_[i].data_))
					{
						ret_value = false;
						break;
					}
					dw_file_offset += dw_write_size;

					if (this->list_pe_section_[i].data_size_ < this->list_pe_section_[i].section_header_.SizeOfRawData) { // padding
						dw_write_size = this->list_pe_section_[i].section_header_.SizeOfRawData - this->list_pe_section_[i].data_size_;

						if (!this->write_zero_memory_to_file(this->h_file_, dw_file_offset, dw_write_size)) {
							ret_value = false;
							break;
						}
						dw_file_offset += dw_write_size;
					}
				}
			}

			// add overlay?
			if (this->overlay_size_ && this->overlay_data_) {
				dw_write_size = this->overlay_size_;
				if (!process_access_help::write_memory_to_file(this->h_file_, dw_file_offset, dw_write_size, this->overlay_data_)) {
					ret_value = false;
				}
				dw_file_offset += dw_write_size;
			}

			SetEndOfFile(this->h_file_);

			this->close_file_handle();
		}

		return ret_value;
	}

	void pe_parser::remove_dos_stub() {
		if (this->p_dos_header_) {
			this->dos_stub_size_ = 0;
			this->p_dos_stub_ = nullptr; // must not delete[]
			this->p_dos_header_->e_lfanew = sizeof(IMAGE_DOS_HEADER);
		}
	}

	void pe_parser::align_all_section_headers() {
		DWORD section_alignment = 0;
		DWORD file_alignment = 0;
		DWORD new_file_size = 0;

		if (this->is_pe_32()) {
			section_alignment = this->p_nt_header32_->OptionalHeader.SectionAlignment;
			file_alignment = this->p_nt_header32_->OptionalHeader.FileAlignment;
		}
		else {
			section_alignment = this->p_nt_header64_->OptionalHeader.SectionAlignment;
			file_alignment = this->p_nt_header64_->OptionalHeader.FileAlignment;
		}

		std::sort(this->list_pe_section_.begin(), this->list_pe_section_.end(), pe_file_section_sort_by_pointer_to_raw_data); // sort by PointerToRawData ascending

		new_file_size = this->p_dos_header_->e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER) + this->p_nt_header32_->FileHeader.SizeOfOptionalHeader
			+ (this->get_number_of_sections() * sizeof(IMAGE_SECTION_HEADER));

		for (WORD i = 0; i < this->get_number_of_sections(); i++) {
			this->list_pe_section_[i].section_header_.VirtualAddress = this->align_value(this->list_pe_section_[i].section_header_.VirtualAddress, section_alignment);
			this->list_pe_section_[i].section_header_.Misc.VirtualSize = this->align_value(this->list_pe_section_[i].section_header_.Misc.VirtualSize, section_alignment);

			this->list_pe_section_[i].section_header_.PointerToRawData = this->align_value(new_file_size, file_alignment);
			this->list_pe_section_[i].section_header_.SizeOfRawData = this->align_value(this->list_pe_section_[i].data_size_, file_alignment);

			new_file_size = this->list_pe_section_[i].section_header_.PointerToRawData + this->list_pe_section_[i].section_header_.SizeOfRawData;
		}

		std::sort(this->list_pe_section_.begin(), this->list_pe_section_.end(), pe_file_section_sort_by_virtual_address); // sort by VirtualAddress ascending
	}

	void pe_parser::fix_pe_header() {
		DWORD dwSize = this->p_dos_header_->e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER);

		if (this->is_pe_32()) {
			//delete bound import directories
			this->p_nt_header32_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress = 0;
			this->p_nt_header32_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size = 0;

			//max 16, zeroing possible garbage values
			for (DWORD i = this->p_nt_header32_->OptionalHeader.NumberOfRvaAndSizes; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++) {
				this->p_nt_header32_->OptionalHeader.DataDirectory[i].Size = 0;
				this->p_nt_header32_->OptionalHeader.DataDirectory[i].VirtualAddress = 0;
			}

			this->p_nt_header32_->OptionalHeader.NumberOfRvaAndSizes = IMAGE_NUMBEROF_DIRECTORY_ENTRIES;
			this->p_nt_header32_->FileHeader.SizeOfOptionalHeader = sizeof(IMAGE_OPTIONAL_HEADER32);

			this->p_nt_header32_->OptionalHeader.SizeOfImage = this->get_section_header_based_size_of_image();

			if (this->module_base_address_) {
				this->p_nt_header32_->OptionalHeader.ImageBase = static_cast<std::uint32_t>(this->module_base_address_);
			}

			this->p_nt_header32_->OptionalHeader.SizeOfHeaders = this->align_value(dwSize + this->p_nt_header32_->FileHeader.SizeOfOptionalHeader
				+ (this->get_number_of_sections() * sizeof(IMAGE_SECTION_HEADER)), this->p_nt_header32_->OptionalHeader.FileAlignment);
		}
		else {
			//delete bound import directories
			this->p_nt_header64_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress = 0;
			this->p_nt_header64_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size = 0;

			//max 16, zeroing possible garbage values
			for (DWORD i = this->p_nt_header64_->OptionalHeader.NumberOfRvaAndSizes; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++) {
				this->p_nt_header64_->OptionalHeader.DataDirectory[i].Size = 0;
				this->p_nt_header64_->OptionalHeader.DataDirectory[i].VirtualAddress = 0;
			}

			this->p_nt_header64_->OptionalHeader.NumberOfRvaAndSizes = IMAGE_NUMBEROF_DIRECTORY_ENTRIES;
			this->p_nt_header64_->FileHeader.SizeOfOptionalHeader = sizeof(IMAGE_OPTIONAL_HEADER64);

			this->p_nt_header64_->OptionalHeader.SizeOfImage = this->get_section_header_based_size_of_image();

			if (this->module_base_address_) {
				this->p_nt_header64_->OptionalHeader.ImageBase = this->module_base_address_;
			}

			this->p_nt_header64_->OptionalHeader.SizeOfHeaders = this->align_value(dwSize + this->p_nt_header64_->FileHeader.SizeOfOptionalHeader
				+ (this->get_number_of_sections() * sizeof(IMAGE_SECTION_HEADER)), this->p_nt_header64_->OptionalHeader.FileAlignment);
		}

		this->remove_iat_directory();
	}

	void pe_parser::set_default_file_alignment() {
		if (this->is_pe_32()) {
			this->p_nt_header32_->OptionalHeader.FileAlignment = file_alignment_constant;
		}
		else {
			this->p_nt_header64_->OptionalHeader.FileAlignment = file_alignment_constant;
		}
	}

	bool pe_parser::dump_process(std::uintptr_t mod_base, std::uintptr_t entry_point, const wchar_t* dump_file_path) {
		this->module_base_address_ = mod_base;

		if (this->read_pe_sections_from_process()) {
			this->set_default_file_alignment();

			this->set_entry_point_va(entry_point);

			this->align_all_section_headers();
			this->fix_pe_header();

			this->get_file_overlay();

			return this->save_pe_file_to_disk(dump_file_path);
		}

		return false;
	}

	bool pe_parser::dump_process(std::uintptr_t mod_base, std::uintptr_t entry_point, const wchar_t* dump_file_path, std::vector<pe_section>& section_list) {
		if (this->list_pe_section_.size() == section_list.size()) {
			for (int i = this->get_number_of_sections() - 1; i >= 0; i--) {
				if (!section_list[i].is_dumped_) {
					this->list_pe_section_.erase(this->list_pe_section_.begin() + i);
					this->set_number_of_sections(this->get_number_of_sections() - 1);
				}
				else {
					this->list_pe_section_[i].section_header_.Misc.VirtualSize = section_list[i].virtual_size_;
					this->list_pe_section_[i].section_header_.SizeOfRawData = section_list[i].raw_size_;
					this->list_pe_section_[i].section_header_.Characteristics = section_list[i].characteristics_;
				}
			}
		}

		return this->dump_process(mod_base, entry_point, dump_file_path);
	}

	void pe_parser::set_entry_point_va(std::uintptr_t entry_point) {
		this->set_entry_point_rva(static_cast<std::uint32_t>(entry_point - this->module_base_address_));
	}

	void pe_parser::set_entry_point_rva(std::uint32_t entry_point) {
		if (this->is_pe_32()) {
			this->p_nt_header32_->OptionalHeader.AddressOfEntryPoint = entry_point;
		}
		else if (this->is_pe_64()) {
			this->p_nt_header64_->OptionalHeader.AddressOfEntryPoint = entry_point;
		}
	}

	bool pe_parser::update_pe_header_checksum(const wchar_t* target_file, std::uint32_t file_size) {
		PIMAGE_NT_HEADERS32 p_nt_header32 = 0;
		PIMAGE_NT_HEADERS64 p_nt_header64 = 0;
		DWORD header_sum = 0;
		DWORD check_sum = 0;
		bool ret_value = false;

		if (!file_size) {
			return ret_value;
		}

		HANDLE h_file_to_map = CreateFileW(target_file, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		if (h_file_to_map != INVALID_HANDLE_VALUE) {
			HANDLE h_mapped_file = CreateFileMapping(h_file_to_map, 0, PAGE_READWRITE, 0, 0, 0);
			if (h_mapped_file) {
				if (GetLastError() != ERROR_ALREADY_EXISTS) {
					LPVOID addrMappedDll = MapViewOfFile(h_mapped_file, FILE_MAP_ALL_ACCESS, 0, 0, 0);

					if (addrMappedDll) {
						p_nt_header32 = (PIMAGE_NT_HEADERS32)CheckSumMappedFile(addrMappedDll, file_size, &header_sum, &check_sum);

						if (p_nt_header32) {
							if (p_nt_header32->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
								p_nt_header64 = (PIMAGE_NT_HEADERS64)p_nt_header32;
								p_nt_header64->OptionalHeader.CheckSum = check_sum;
							}
							else {
								p_nt_header32->OptionalHeader.CheckSum = check_sum;
							}

							ret_value = true;
						}

						UnmapViewOfFile(addrMappedDll);
					}
				}
				CloseHandle(h_mapped_file);
			}
			CloseHandle(h_file_to_map);
		}

		return ret_value;
	}

	std::uint8_t* pe_parser::get_section_memory_by_index(int index) {
		return this->list_pe_section_[index].data_;
	}

	std::uint32_t pe_parser::get_section_memory_size_by_index(int index) {
		return this->list_pe_section_[index].data_size_;
	}

	int pe_parser::convert_rva_to_offset_vector_index(std::uintptr_t dw_rva) {
		for (WORD i = 0; i < this->get_number_of_sections(); i++) {
			if (this->list_pe_section_[i].section_header_.VirtualAddress <= dw_rva
				&& this->list_pe_section_[i].section_header_.VirtualAddress + this->list_pe_section_[i].section_header_.Misc.VirtualSize > dw_rva)
			{
				return i;
			}
		}

		return -1;
	}

	std::uintptr_t pe_parser::convert_offset_to_rva_vector(std::uintptr_t dw_offset) {
		for (WORD i = 0; i < this->get_number_of_sections(); i++) {
			if (this->list_pe_section_[i].section_header_.PointerToRawData <= dw_offset
				&& this->list_pe_section_[i].section_header_.PointerToRawData + this->list_pe_section_[i].section_header_.SizeOfRawData > dw_offset)
			{
				return (dw_offset - this->list_pe_section_[i].section_header_.PointerToRawData) + this->list_pe_section_[i].section_header_.VirtualAddress;
			}
		}

		return NULL;
	}

	std::uintptr_t pe_parser::convert_rva_to_offset_vector(std::uintptr_t dw_rva) {
		for (WORD i = 0; i < this->get_number_of_sections(); i++) {
			if (this->list_pe_section_[i].section_header_.VirtualAddress <= dw_rva
				&& this->list_pe_section_[i].section_header_.VirtualAddress + this->list_pe_section_[i].section_header_.Misc.VirtualSize > dw_rva)
			{
				return (dw_rva - this->list_pe_section_[i].section_header_.VirtualAddress) + this->list_pe_section_[i].section_header_.PointerToRawData;
			}
		}

		return 0;
	}

	std::uintptr_t pe_parser::convert_rva_to_offset_relative(std::uintptr_t dw_rva) {
		for (WORD i = 0; i < this->get_number_of_sections(); i++) {
			if (this->list_pe_section_[i].section_header_.VirtualAddress <= dw_rva
				&& this->list_pe_section_[i].section_header_.VirtualAddress + this->list_pe_section_[i].section_header_.Misc.VirtualSize > dw_rva)
			{
				return (dw_rva - this->list_pe_section_[i].section_header_.VirtualAddress);
			}
		}

		return 0;
	}

	std::uint32_t pe_parser::get_section_address_rva_by_index(int index) {
		return this->list_pe_section_[index].section_header_.VirtualAddress;
	}

	PIMAGE_NT_HEADERS pe_parser::get_current_nt_header() {
#		ifdef _WIN64
			return this->p_nt_header64_;
#		else
			return this->p_nt_header32_;
#		endif
	}

	bool pe_parser::read_pe_header_from_file(bool read_section_headers) {
		bool rev_value = false;
		DWORD correct_size = 0;
		DWORD number_of_bytes_read = 0;

		DWORD read_size = this->get_initial_header_read_size(read_section_headers);

		this->header_memory_ = new BYTE[read_size];

		if (this->open_file_handle()) {
			this->file_size_ = static_cast<std::uint32_t>(process_access_help::get_file_size(this->h_file_));

			if (ReadFile(this->h_file_, this->header_memory_, read_size, &number_of_bytes_read, 0)) {
				rev_value = true;

				this->get_dos_and_nt_header(this->header_memory_, static_cast<LONG>(read_size));

				if (this->is_valid_pe_file()) {
					correct_size = this->calc_correct_pe_header_size(read_section_headers);

					if (read_size < correct_size) {
						read_size = correct_size;

						if (this->file_size_ > 0) {
							if (this->file_size_ < correct_size) {
								read_size = this->file_size_;
							}
						}

						delete[] this->header_memory_;
						this->header_memory_ = new BYTE[read_size];

						SetFilePointer(this->h_file_, 0, 0, FILE_BEGIN);

						if (ReadFile(this->h_file_, this->header_memory_, read_size, &number_of_bytes_read, 0)) {
							this->get_dos_and_nt_header(this->header_memory_, static_cast<LONG>(read_size));
						}
					}
				}
			}

			this->close_file_handle();
		}

		return rev_value;
	}

	bool pe_parser::read_pe_header_from_process(bool read_section_headers) {
		bool ret_value = false;
		DWORD correct_size = 0;

		DWORD read_size = this->get_initial_header_read_size(read_section_headers);

		this->header_memory_ = new BYTE[read_size];

		if (process_access_help::read_memory_partly_from_process(this->module_base_address_, read_size, this->header_memory_)) {
			ret_value = true;

			this->get_dos_and_nt_header(this->header_memory_, (LONG)read_size);

			if (this->is_valid_pe_file()) {
				correct_size = this->calc_correct_pe_header_size(read_section_headers);

				if (read_size < correct_size) {
					read_size = correct_size;
					delete[] this->header_memory_;
					this->header_memory_ = new BYTE[read_size];

					if (process_access_help::read_memory_partly_from_process(this->module_base_address_, read_size, this->header_memory_)) {
						this->get_dos_and_nt_header(this->header_memory_, (LONG)read_size);
					}
				}
			}
		}

		return ret_value;
	}

	bool pe_parser::has_directory(const int directory_index) {
		if (this->is_pe_32()) {
			return this->p_nt_header32_->OptionalHeader.DataDirectory[directory_index].VirtualAddress != NULL;
		}

		if (this->is_pe_64()) {
			return this->p_nt_header64_->OptionalHeader.DataDirectory[directory_index].VirtualAddress != NULL;
		}

		return false;
	}

	bool pe_parser::get_section_headers() {
		PIMAGE_SECTION_HEADER section_header = IMAGE_FIRST_SECTION(this->p_nt_header32_);

		pe_file_section section;

		this->list_pe_section_.clear();
		this->list_pe_section_.reserve(this->get_number_of_sections());

		for (std::uint16_t i = 0; i < this->get_number_of_sections(); i++) {
			memcpy_s(&section.section_header_, sizeof(IMAGE_SECTION_HEADER), section_header, sizeof(IMAGE_SECTION_HEADER));

			this->list_pe_section_.push_back(section);
			section_header++;
		}

		return true;
	}

	void pe_parser::get_dos_and_nt_header(std::uint8_t* memory, LONG size) {
		this->p_dos_header_ = reinterpret_cast<PIMAGE_DOS_HEADER>(memory);

		this->p_nt_header32_ = nullptr;
		this->p_nt_header64_ = nullptr;
		this->dos_stub_size_ = 0;
		this->p_dos_stub_ = nullptr;

		if (this->p_dos_header_->e_lfanew > 0 && this->p_dos_header_->e_lfanew < size) { // malformed PE
			this->p_nt_header32_ = reinterpret_cast<PIMAGE_NT_HEADERS32>(reinterpret_cast<std::uintptr_t>(this->p_dos_header_) + this->p_dos_header_->e_lfanew);
			this->p_nt_header64_ = reinterpret_cast<PIMAGE_NT_HEADERS64>(reinterpret_cast<std::uintptr_t>(this->p_dos_header_) + this->p_dos_header_->e_lfanew);

			if (this->p_dos_header_->e_lfanew > sizeof(IMAGE_DOS_HEADER)) {
				this->dos_stub_size_ = this->p_dos_header_->e_lfanew - sizeof(IMAGE_DOS_HEADER);
				this->p_dos_stub_ = reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(this->p_dos_header_) + sizeof(IMAGE_DOS_HEADER));
			}
			else if (this->p_dos_header_->e_lfanew < sizeof(IMAGE_DOS_HEADER)) {
				// Overlapped Headers, e.g. Spack (by Bagie)
				this->p_dos_header_->e_lfanew = sizeof(IMAGE_DOS_HEADER);
			}
		}
	}

	std::uint32_t pe_parser::calc_correct_pe_header_size(bool read_section_headers) {
		DWORD correct_size = this->p_dos_header_->e_lfanew + 50; //extra buffer

		if (read_section_headers) {
			correct_size += this->get_number_of_sections() * sizeof(IMAGE_SECTION_HEADER);
		}

		if (this->is_pe_32()) {
			correct_size += sizeof(IMAGE_NT_HEADERS32);
		}
		else if (this->is_pe_64()) {
			correct_size += sizeof(IMAGE_NT_HEADERS64);
		}
		else {
			correct_size = 0; // not a valid PE
		}

		return correct_size;
	}

	std::uint32_t pe_parser::get_initial_header_read_size(bool read_section_headers) {
		_Unreferenced_parameter_(read_section_headers);

		return sizeof(IMAGE_DOS_HEADER) + 0x300 + sizeof(IMAGE_NT_HEADERS64);
	}

	bool pe_parser::open_file_handle() {
		if (this->h_file_ == INVALID_HANDLE_VALUE) {
			if (this->filename_) {
				this->h_file_ = CreateFileW(this->filename_, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
			}
			else {
				this->h_file_ = INVALID_HANDLE_VALUE;
			}
		}

		return this->h_file_ != INVALID_HANDLE_VALUE;
	}

	void pe_parser::close_file_handle() {
		if (this->h_file_ != INVALID_HANDLE_VALUE) {
			CloseHandle(this->h_file_);
			this->h_file_ = INVALID_HANDLE_VALUE;
		}
	}

	std::uint32_t pe_parser::is_memory_not_null(std::uint8_t* data, int data_size) {
		for (int i = data_size - 1; i >= 0; i--) {
			if (data[i] != 0) {
				return i + 1;
			}
		}

		return 0;
	}

	bool pe_parser::open_write_file_handle(const wchar_t* new_file) {
		if (new_file) {
			this->h_file_ = CreateFileW(new_file, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		}
		else {
			this->h_file_ = INVALID_HANDLE_VALUE;
		}

		return this->h_file_ != INVALID_HANDLE_VALUE;
	}

	bool pe_parser::write_zero_memory_to_file(HANDLE hFile, std::uint32_t file_offset, std::uint32_t size) {
		bool ret_value = false;
		PVOID zero_memory = calloc(size, 1);

		if (zero_memory) {
			ret_value = process_access_help::write_memory_to_file(hFile, file_offset, size, zero_memory);
			free(zero_memory);
		}

		return ret_value;
	}

	bool pe_parser::read_pe_section_from_file(std::uint32_t read_offset, pe_file_section& section) {
		DWORD bytes_read = 0;
		section.data_ = new BYTE[section.data_size_];
		SetFilePointer(this->h_file_, read_offset, 0, FILE_BEGIN);
		return ReadFile(this->h_file_, section.data_, section.data_size_, &bytes_read, 0) != FALSE;
	}

	bool pe_parser::read_pe_section_from_process(std::uintptr_t read_offset, pe_file_section& section) {
		section.data_ = new BYTE[section.data_size_];
		return process_access_help::read_memory_partly_from_process(read_offset, section.data_size_, section.data_);
	}

	bool pe_parser::read_section_from_process(const std::uintptr_t read_offset, pe_file_section& section) {
		return this->read_section_from(read_offset, section, true); // process
	}

	bool pe_parser::read_section_from_file(const std::uint32_t read_offset, pe_file_section& section) {
		return this->read_section_from(read_offset, section, false); // file
	}

	bool pe_parser::read_section_from(const std::uintptr_t read_offset, pe_file_section& section, const bool is_process) {
		const std::uint32_t max_read_size = 100;
		std::uint32_t current_read_size;
		BYTE data[max_read_size];
		bool ret_value = true;
		std::uint32_t values_found = 0;
		std::uint32_t read_size = 0;
		std::uintptr_t current_offset = 0;

		section.data_ = 0;
		section.data_size_ = 0;
		read_size = section.normal_size_;

		if (!read_offset || !read_size) {
			return true; // section without data is valid
		}

		if (read_size <= max_read_size) {
			section.data_size_ = read_size;
			section.normal_size_ = read_size;

			if (is_process) {
				return this->read_pe_section_from_process(read_offset, section);
			}
			else {
				return this->read_pe_section_from_file(static_cast<std::uint32_t>(read_offset), section);
			}
		}

		current_read_size = read_size % max_read_size; // alignment %

		if (!current_read_size) {
			current_read_size = max_read_size;
		}
		current_offset = read_offset + read_size - current_read_size;

		while (current_offset >= read_offset) { // start from the end
			ZeroMemory(data, current_read_size);

			if (is_process) {
				ret_value = process_access_help::read_memory_partly_from_process(current_offset, current_read_size, data);
			}
			else {
				ret_value = process_access_help::read_memory_from_file(this->h_file_, static_cast<int>(current_offset), current_read_size, data);
			}

			if (!ret_value) {
				break;
			}

			values_found = this->is_memory_not_null(data, current_read_size);
			if (values_found) {
				//found some real code

				current_offset += values_found;

				if (read_offset < current_offset) {
					//real size
					section.data_size_ = (DWORD)(current_offset - read_offset);

					//some safety space because of something like this at the end of a section:
					//FF25 C0604000 JMP DWORD PTR DS:[<&KERNEL32.RtlUnwind>]
					section.data_size_ += sizeof(DWORD);

					if (section.normal_size_ < section.data_size_) {
						section.data_size_ = section.normal_size_;
					}
				}

				break;
			}

			current_read_size = max_read_size;
			current_offset -= current_read_size;
		}

		if (section.data_size_) {
			if (is_process) {
				ret_value = this->read_pe_section_from_process(read_offset, section);
			}
			else {
				ret_value = this->read_pe_section_from_file(static_cast<std::uint32_t>(read_offset), section);
			}
		}

		return ret_value;
	}

	std::uintptr_t pe_parser::get_standard_image_base() {
		if (this->is_pe_32()) {
			return this->p_nt_header32_->OptionalHeader.ImageBase;
		}
		else {
			return this->p_nt_header64_->OptionalHeader.ImageBase;
		}
	}

	bool pe_parser::add_new_last_section(const char* section_name, std::uint32_t section_size, std::uint8_t* section_data) {
		size_t name_length = strlen(section_name);
		DWORD file_alignment = 0, section_alignment = 0;
		pe_file_section section;

		if (name_length > IMAGE_SIZEOF_SHORT_NAME) {
			return false;
		}

		if (this->is_pe_32()) {
			file_alignment = this->p_nt_header32_->OptionalHeader.FileAlignment;
			section_alignment = this->p_nt_header32_->OptionalHeader.SectionAlignment;
		}
		else {
			file_alignment = this->p_nt_header64_->OptionalHeader.FileAlignment;
			section_alignment = this->p_nt_header64_->OptionalHeader.SectionAlignment;
		}

		memcpy_s(section.section_header_.Name, IMAGE_SIZEOF_SHORT_NAME, section_name, name_length);

		// last section doesn't need SizeOfRawData alignment
		section.section_header_.SizeOfRawData = section_size; // alignValue(sectionSize, file_alignment);
		section.section_header_.Misc.VirtualSize = this->align_value(section_size, section_alignment);

		section.section_header_.PointerToRawData = this->align_value(this->get_section_header_based_file_size(), file_alignment);
		section.section_header_.VirtualAddress = this->align_value(this->get_section_header_based_size_of_image(), section_alignment);

		section.section_header_.Characteristics = IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE | IMAGE_SCN_CNT_CODE | IMAGE_SCN_CNT_INITIALIZED_DATA;

		section.normal_size_ = section.section_header_.SizeOfRawData;
		section.data_size_ = section.section_header_.SizeOfRawData;

		if (section_data == 0) {
			section.data_ = new BYTE[section.section_header_.SizeOfRawData];
			ZeroMemory(section.data_, section.section_header_.SizeOfRawData);
		}
		else {
			section.data_ = section_data;
		}

		this->list_pe_section_.push_back(section);

		this->set_number_of_sections(this->get_number_of_sections() + 1);

		return true;
	}

	std::uint32_t pe_parser::align_value(std::uint32_t bad_value, std::uint32_t align_to) {
		return ((bad_value + align_to - 1) / align_to) * align_to;
	}

	void pe_parser::set_number_of_sections(std::uint16_t number_of_sections) {
		this->p_nt_header32_->FileHeader.NumberOfSections = number_of_sections;
	}

	void pe_parser::remove_iat_directory() {
		DWORD searchAddress = 0;

		if (this->is_pe_32()) {
			searchAddress = this->p_nt_header32_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress;

			this->p_nt_header32_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress = NULL;
			this->p_nt_header32_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size = 0;
		}
		else {
			searchAddress = this->p_nt_header64_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress;

			this->p_nt_header64_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress = NULL;
			this->p_nt_header64_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size = 0;
		}

		if (searchAddress) {
			for (WORD i = 0; i < this->get_number_of_sections(); i++) {
				if (this->list_pe_section_[i].section_header_.VirtualAddress <= searchAddress
					&& this->list_pe_section_[i].section_header_.VirtualAddress + this->list_pe_section_[i].section_header_.Misc.VirtualSize > searchAddress)
				{
					// section must be read and writable
					this->list_pe_section_[i].section_header_.Characteristics |= IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE;
				}
			}
		}
	}

	bool pe_parser::get_file_overlay() {
		DWORD number_of_bytes_read;
		bool ret_value = false;

		if (!this->has_overlay_data()) {
			return false;
		}

		if (this->open_file_handle()) {
			std::uint32_t overlay_offset = this->get_section_header_based_file_size();
			std::uint32_t file_size = static_cast<std::uint32_t>(process_access_help::get_file_size(this->h_file_));
			this->overlay_size_ = file_size - overlay_offset;

			this->overlay_data_ = new BYTE[this->overlay_size_];

			SetFilePointer(this->h_file_, overlay_offset, 0, FILE_BEGIN);

			if (ReadFile(this->h_file_, this->overlay_data_, this->overlay_size_, &number_of_bytes_read, 0)) {
				ret_value = true;
			}

			this->close_file_handle();
		}

		return ret_value;
	}
}
