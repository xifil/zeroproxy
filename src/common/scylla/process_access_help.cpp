#include "scylla/scylla_common.hpp"

#include "scylla/process_access_help.hpp"
#include "utils/nt.hpp"

namespace scylla {
	HANDLE process_access_help::h_process = nullptr;

	LONGLONG process_access_help::get_file_size(HANDLE h_file) {
		LARGE_INTEGER lp_file_size = { 0 };

		if (h_file != INVALID_HANDLE_VALUE && h_file != 0) {
			if (GetFileSizeEx(h_file, &lp_file_size)) {
				return lp_file_size.QuadPart;
			}
		}

		return 0;
	}

	LONGLONG process_access_help::get_file_size(const wchar_t* file_path) {
		LONGLONG file_size = 0;
		HANDLE h_file = CreateFileW(file_path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);

		if (h_file != INVALID_HANDLE_VALUE) {
			file_size = get_file_size(h_file);
			CloseHandle(h_file);
		}

		return file_size;
	}

	bool process_access_help::read_memory_from_process(std::uintptr_t address, std::size_t size, LPVOID data_buffer) {
		SIZE_T lp_number_of_bytes_read = 0;
		DWORD dw_protect = 0;
		bool return_value = false;

		if (!h_process) {
			return return_value;
		}

		if (!ReadProcessMemory(h_process, (LPVOID)address, data_buffer, size, &lp_number_of_bytes_read)) {
			if (!VirtualProtectEx(h_process, (LPVOID)address, size, PAGE_READWRITE, &dw_protect)) {
				return_value = false;
			}
			else {
				return_value = ReadProcessMemory(h_process, (LPVOID)address, data_buffer, size, &lp_number_of_bytes_read);
				VirtualProtectEx(h_process, (LPVOID)address, size, dw_protect, &dw_protect);
			}
		}
		else {
			return_value = true;
		}

		return return_value && size == lp_number_of_bytes_read;
	}

	bool process_access_help::read_memory_partly_from_process(std::uintptr_t address, std::size_t size, LPVOID data_buffer) {
		DWORD_PTR address_part = 0;
		DWORD_PTR read_bytes = 0;
		DWORD_PTR bytes_to_read = 0;
		MEMORY_BASIC_INFORMATION mem_basic = { 0 };
		bool return_value = false;

		if (!h_process) {
			return return_value;
		}

		if (!read_memory_from_process(address, size, data_buffer)) {
			address_part = address;

			do {
				if (!VirtualQueryEx(h_process, (LPCVOID)address_part, &mem_basic, sizeof(mem_basic))) {
					break;
				}

				bytes_to_read = mem_basic.RegionSize;

				if ((read_bytes + bytes_to_read) > size) {
					bytes_to_read = size - read_bytes;
				}

				if (mem_basic.State == MEM_COMMIT) {
					if (!read_memory_from_process(address_part, bytes_to_read, (LPVOID)((DWORD_PTR)data_buffer + read_bytes))) {
						break;
					}
				}
				else {
					ZeroMemory((LPVOID)((DWORD_PTR)data_buffer + read_bytes), bytes_to_read);
				}

				read_bytes += bytes_to_read;
				address_part += mem_basic.RegionSize;
			} while (read_bytes < size);

			if (read_bytes == size) {
				return_value = true;
			}
		}
		else {
			return_value = true;
		}

		return return_value;
	}

	bool process_access_help::read_memory_from_file(HANDLE h_file, LONG offset, DWORD size, LPVOID data_buffer) {
		DWORD lp_number_of_bytes_read = 0;
		DWORD ret_value = 0;
		DWORD dw_error = 0;

		if (h_file != INVALID_HANDLE_VALUE) {
			ret_value = SetFilePointer(h_file, offset, NULL, FILE_BEGIN);
			dw_error = GetLastError();

			if (ret_value == INVALID_SET_FILE_POINTER && dw_error != NO_ERROR) {
				return false;
			}

			return ReadFile(h_file, data_buffer, size, &lp_number_of_bytes_read, 0);
		}

		return false;
	}

	bool process_access_help::write_memory_to_file(HANDLE h_file, LONG offset, DWORD size, LPCVOID data_buffer) {
		DWORD lp_number_of_bytes_written = 0;
		DWORD ret_value = 0;
		DWORD dw_error = 0;

		if (h_file != INVALID_HANDLE_VALUE && data_buffer) {
			ret_value = SetFilePointer(h_file, offset, NULL, FILE_BEGIN);
			dw_error = GetLastError();

			if (ret_value == INVALID_SET_FILE_POINTER && dw_error != NO_ERROR) {
				return false;
			}

			return WriteFile(h_file, data_buffer, size, &lp_number_of_bytes_written, 0);
		}

		return false;
	}

	bool process_access_help::open_process_handle(DWORD dw_pid) {
		if (dw_pid <= 0 || h_process) {
			return false;
		}

		h_process = native_open_process(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE
			| PROCESS_SUSPEND_RESUME | PROCESS_TERMINATE, dw_pid);
		return h_process != nullptr;
	}

	HANDLE process_access_help::native_open_process(DWORD dw_desired_access, DWORD dw_process_id) {
		static utils::nt::library ntdll{ "ntdll.dll" };

		HANDLE process = nullptr;
		CLIENT_ID cid{ 0 };
		OBJECT_ATTRIBUTES object_attrib;

		InitializeObjectAttributes(&object_attrib, 0, 0, 0, 0);
#		pragma warning(disable : 4312)
		cid.UniqueProcess = reinterpret_cast<HANDLE>(dw_process_id);

		if (NT_SUCCESS(ntdll.invoke<NTSTATUS>("NtOpenProcess", &process, dw_desired_access, &object_attrib, &cid))) {
			return process;
		}

		return nullptr;
	}
}
