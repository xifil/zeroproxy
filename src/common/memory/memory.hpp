#pragma once
#include "common_core.hpp"
#include "logger/logger.hpp"
#include "memory/scanned_result.hpp"
#include "utils/nt.hpp"

namespace memory {
	struct masked_signature {
		std::vector<std::uint8_t> data_{};
		std::vector<std::uint8_t> mask_{};
	};

	inline masked_signature masked_signature_from_string(const std::string& pattern) {
		masked_signature sig{};
		char* base = const_cast<char*>(pattern.c_str());

		for (char* cur = base; cur < base + pattern.length(); cur++) {
			if ('\?' != *cur) { // check is ?
				sig.data_.push_back(strtoul(cur, &cur, 16) & 0xFF);
				sig.mask_.push_back('x');
				continue;
			}

			cur++;
			if ('\?' == *cur) { // check is double ?
				cur++;
			}

			sig.data_.push_back(0xFF);
			sig.mask_.push_back('?');
		}

		return sig;
	}

	template <typename T = void*>
	std::enable_if_t<std::is_pointer_v<T>, std::vector<scanned_result<std::remove_pointer_t<T>>>> masked_vectored_sig_scan(utils::nt::library library,
		masked_signature sig, std::size_t limit)
	{
		std::size_t pat_len = sig.mask_.size();
		MODULEINFO mod_info = library.get_info();
		std::uintptr_t mod_base = PTR_AS(std::uintptr_t, mod_info.lpBaseOfDll);
		std::uintptr_t mod_len = mod_info.SizeOfImage;
		std::vector<scanned_result<std::remove_pointer_t<T>>> results{};

#		if defined(_WIN64)
			MEMORY_BASIC_INFORMATION64 page_info = {};
#			define PAGE_BASE_ADDR(p) p.BaseAddress
#		else
			MEMORY_BASIC_INFORMATION page_info = {};
#			define PAGE_BASE_ADDR(p) PTR_AS(std::uintptr_t, p.BaseAddress)
#		endif
		for (auto current_page = mod_base; current_page < mod_base + mod_len; current_page = PAGE_BASE_ADDR(page_info) + page_info.RegionSize) {
			VirtualQuery(PTR_AS(LPCVOID, current_page), PTR_AS(PMEMORY_BASIC_INFORMATION, &page_info), sizeof(MEMORY_BASIC_INFORMATION));
			if (page_info.Protect == PAGE_NOACCESS || page_info.State != MEM_COMMIT || page_info.Protect & PAGE_GUARD) {
				continue;
			}

			for (auto current_addr = PAGE_BASE_ADDR(page_info); current_addr < PAGE_BASE_ADDR(page_info) + page_info.RegionSize - 0x8; current_addr++) {
				if (current_addr >= mod_base + mod_len - pat_len) {
					continue;
				}

				bool found = true;

				for (std::size_t jx = 0; jx < pat_len; jx++) {
					if (sig.mask_[jx] != '?' && sig.data_[jx] != DEREF_PTR_AS(std::uint8_t, current_addr + jx)) {
						found = false;
						break;
					}
				}

				if (found) {
					results.push_back(scanned_result<std::remove_pointer_t<T>>(current_addr));
					if (results.size() >= limit) {
						return results;
					}
				}
			}
		}

		return results;
	}

	template <typename T = void*>
	std::enable_if_t<std::is_pointer_v<T>, scanned_result<std::remove_pointer_t<T>>> masked_sig_scan(utils::nt::library library, masked_signature sig) {
		std::vector<scanned_result<std::remove_pointer_t<T>>> result = masked_vectored_sig_scan<T>(library, sig, 1);
		if (result.size() > 0) {
			return result.at(0);
		}
		return scanned_result<std::remove_pointer_t<T>>(nullptr);
	}

	template <typename T = void*>
	std::enable_if_t<std::is_pointer_v<T>, std::vector<scanned_result<std::remove_pointer_t<T>>>> vectored_sig_scan(utils::nt::library library,
		std::string pattern, std::size_t limit, std::string name = "", bool print_fail = true)
	{
		std::vector<scanned_result<std::remove_pointer_t<T>>> res = masked_vectored_sig_scan<T>(library, masked_signature_from_string(pattern), limit);
		if (!name.empty()) {
			if (res.size() > 0) {
				LOG("Scanner", DEBUG, "Found '{}' {}+0x{:X} [{} total]", name, library.get_name(), res.at(0).as<std::uintptr_t>()
					- PTR_AS(std::uintptr_t, library.get_info().lpBaseOfDll), res.size());
			}
			else if (print_fail) {
				LOG("Scanner", WARN, "Failed to find '{}' in {} ({})", name, library.get_name(), pattern);
			}
		}
		return res;
	}

	template <typename T = void*>
	std::enable_if_t<std::is_pointer_v<T>, scanned_result<std::remove_pointer_t<T>>> sig_scan(utils::nt::library library, std::string pattern,
		std::string name = "", bool print_fail = true)
	{
		scanned_result<std::remove_pointer_t<T>> res = masked_sig_scan<T>(library, masked_signature_from_string(pattern));
		if (!name.empty()) {
			if (res) {
				LOG("Scanner", DEBUG, "Found '{}' {}+0x{:X}", name, library.get_name(), res.as<std::uintptr_t>()
					- PTR_AS(std::uintptr_t, library.get_info().lpBaseOfDll));
			}
			else if (print_fail) {
				LOG("Scanner", WARN, "Failed to find '{}' in {} ({})", name, library.get_name(), pattern);
			}
		}
		return res;
	}

	template <typename T = void*>
	std::enable_if_t<std::is_pointer_v<T>, scanned_result<std::remove_pointer_t<T>>> get_export(const std::string& module_name, const std::string& export_name) {
		utils::nt::library library(module_name);
		if (!library.is_valid()) {
			LOG("Scanner", WARN, "Failed to find module '{}' while trying to find '{}'", export_name, module_name);
			return scanned_result<std::remove_pointer_t<T>>(nullptr);
		}

		scanned_result<std::remove_pointer_t<T>> res = scanned_result<std::remove_pointer_t<T>>(library.get_proc<void*>(export_name));
		if (res) {
			LOG("Scanner", DEBUG, "Found '{}' {}+0x{:X}", export_name, module_name, res.as<std::uintptr_t>()
				- PTR_AS(std::uintptr_t, library.get_info().lpBaseOfDll));
		}
		else {
			LOG("Scanner", WARN, "Failed to find '{}' in {}", export_name, module_name);
		}
		return res;
	}
}