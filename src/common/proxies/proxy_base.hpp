#pragma once
#include "common_core.hpp"
#include <utils/nt.hpp>

#if defined(_WIN64)
#	define PROXY_API
#	define PROXY_EXPORT(name, x86_arg_size, ordinal) "/EXPORT:" #name "=" #name "_ZP,@" #ordinal
#else
#	define PROXY_API __stdcall
#	define PROXY_EXPORT(name, x86_arg_size, ordinal) "/EXPORT:" #name "=_" #name "_ZP@" #x86_arg_size ",@" #ordinal
#endif

namespace proxy {
	template <typename T>
	T get_export(const std::string& lib_name, const std::string& export_name) {
		char dir[MAX_PATH]{ 0 };
#		if defined(_WIN64)
			GetSystemDirectoryA(dir, sizeof(dir));
#		else
			GetSystemWow64DirectoryA(dir, sizeof(dir));
#		endif
	
		const auto lib = utils::nt::library::load(dir + "/"s + lib_name);
		return lib.get_proc<T>(export_name.c_str());
	}
}
