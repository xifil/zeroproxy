#pragma once
#include "scylla/scylla_common.hpp"

#include "scylla/api_info.hpp"
#include "scylla/module_info.hpp"

namespace scylla {
	class process_access_help {
	public:
		static HANDLE h_process; // OpenProcess handle to target process

		static std::uintptr_t target_image_base;
		static std::uintptr_t target_size_of_image;
		static std::uintptr_t max_valid_address;

		static module_info* selectedModule;

		static std::vector<module_info> module_list; // target process module list
		static std::vector<module_info> own_module_list; // own module list

		static const size_t PE_HEADER_BYTES_COUNT = 2000;

		static BYTE file_header_from_disk[PE_HEADER_BYTES_COUNT];

		/*
		 * We don't require the below code as we are only ever dumping the game, we don't require most of this
		 * "process" stuff.
		 */

		/*
		// for decomposer
		static _DInst decomposerResult[MAX_INSTRUCTIONS];
		static unsigned int decomposerInstructionsCount;
		static _CodeInfo decomposerCi;

		// distorm :: Decoded instruction information.
		static _DecodedInst decodedInstructions[MAX_INSTRUCTIONS];
		static unsigned int decodedInstructionsCount;
#		ifdef _WIN64
			static const _DecodeType dt = Decode64Bits;
#		else
			static const _DecodeType dt = Decode32Bits;
#		endif
			*/

		/*
		 * Open a new process handle
		 */
		static bool open_process_handle(DWORD dw_pid);

		static HANDLE native_open_process(DWORD dw_desired_access, DWORD dw_process_id);

		static void close_process_handle();

		/*
		 * Get all modules from a process
		 */
		static bool get_process_modules(HANDLE h_process, std::vector<module_info>& module_list);

		/*
		 * file mapping view with different access level
		 */
		static LPVOID create_file_mapping_view_read(const wchar_t* filePath);
		static LPVOID create_file_mapping_view_full(const wchar_t* filePath);

		/*
		 * Create a file mapping view of a file
		 */
		static LPVOID create_file_mapping_view(const wchar_t* filePath, DWORD accessFile, DWORD flProtect, DWORD accessMap);

		/*
		 * Read memory from target process
		 */
		static bool read_memory_from_process(std::uintptr_t address, std::size_t size, LPVOID data_buffer);
		static bool write_memory_to_process(std::uintptr_t address, std::size_t size, LPVOID data_buffer);

		/*
		 * Read memory from target process and ignore no data pages
		 */
		static bool read_memory_partly_from_process(std::uintptr_t address, std::size_t size, LPVOID data_buffer);

		/*
		 * Read memory from file
		 */
		static bool read_memory_from_file(HANDLE h_file, LONG offset, DWORD size, LPVOID data_buffer);

		/*
		 * Write memory to file
		 */
		static bool write_memory_to_file(HANDLE h_file, LONG offset, DWORD size, LPCVOID data_buffer);

		/*
		 * Write memory to new file
		 */
		static bool write_memory_to_new_file(const wchar_t* file, DWORD size, LPCVOID dataBuffer);

		/*
		 * Write memory to file end
		 */
		static bool write_memory_to_file_end(HANDLE hFile, DWORD size, LPCVOID dataBuffer);

		/*
		 * Disassemble Memory
		 */
		static bool disassemble_memory(BYTE* dataBuffer, SIZE_T bufferSize, std::uintptr_t startOffset);

		static bool decompose_memory(BYTE* dataBuffer, SIZE_T bufferSize, std::uintptr_t startAddress);

		/*
		 * Search for pattern
		 */
		static std::uintptr_t find_pattern(std::uintptr_t startOffset, DWORD size, BYTE* pattern, const char* mask);

		/*
		 * Get process ID by process name
		 */
		static DWORD get_process_by_name(const wchar_t* processName);

		/*
		 * Get memory region from address
		 */
		static bool get_memory_region_from_address(std::uintptr_t address, std::uintptr_t* memoryRegionBase, SIZE_T* memoryRegionSize);

		/*
		 * Read PE Header from file
		 */
		static bool read_header_from_file(BYTE* buffer, DWORD buffer_size, const wchar_t* file_path);

		static bool read_header_from_current_file(const wchar_t* file_path);

		/*
		 * Get real sizeOfImage value
		 */
		static SIZE_T get_size_of_image_process(HANDLE process_handle, std::uintptr_t module_base);

		/*
		 * Get real sizeOfImage value current process
		 */
		static bool get_size_of_image_current_process();

		static LONGLONG get_file_size(HANDLE h_file);
		static LONGLONG get_file_size(const wchar_t* file_path);

		static DWORD get_entry_point_from_file(const wchar_t* file_path);

		static bool create_backup_file(const wchar_t* file_path);

		static DWORD get_module_handles_from_process(const HANDLE h_process, HMODULE** h_mods);

		static void set_current_process_as_target();

		static bool suspend_process();
		static bool resume_process();
		static bool terminate_process();
		static bool is_page_executable(DWORD protect);
		static bool is_page_accessable(DWORD protect);
		static std::size_t get_size_of_image_process_native(HANDLE process_handle, std::uintptr_t module_base);
	};
}
