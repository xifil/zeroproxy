#include "common_core.hpp"
#include "utils/nt.hpp"

extern "C" {
	int s_read_arc4random(void*, std::size_t) {
		return -1;
	}

	int s_read_getrandom(void*, std::size_t) {
		return -1;
	}

	int s_read_urandom(void*, std::size_t) {
		return -1;
	}

	int s_read_ltm_rng(void*, std::size_t) {
		return -1;
	}
}

std::uintptr_t operator ""_b(unsigned long long int val) {
	static utils::nt::library game{};
	return PTR_AS(std::uintptr_t, game.get_ptr()) + static_cast<std::uintptr_t>(val);
}

std::string and_rel(std::uintptr_t address) {
	if (utils::nt::library assigned_lib = utils::nt::library::get_by_address(PTR_AS(void*, address))) {
		return std::format("0x" FMT_PTR " ({}+0x" FMT_PTR ")", address, assigned_lib.get_name(), address - PTR_AS(std::uintptr_t, assigned_lib.get_ptr()));
	}
	return std::format("0x" FMT_PTR, address);
}
