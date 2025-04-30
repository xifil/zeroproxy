#pragma once
#include "common.hpp"
#include "game/function_types.hpp"

namespace dvars {
	inline constexpr std::int64_t NUM_START = 0xCBF29CE484222325;

	inline std::int64_t hash_fnv(std::int64_t start, const std::string& input) {
		std::uint64_t num = static_cast<std::uint64_t>(start);
		for (std::size_t index = 0; index < input.length(); ++index) {
			num ^= std::tolower(input[index]);
			num *= 0x00000100000001B3;
		}
		return num & 0x7FFFFFFFFFFFFFFF;
	}

	inline std::int64_t hash_fnv(const std::string& input) {
		return hash_fnv(NUM_START, input);
	}

	t9::dvar_t* get_dvar_by_hash(std::int64_t hash);

	inline t9::dvar_t* get_dvar_by_name(const std::string& name) {
		return get_dvar_by_hash(hash_fnv(name));
	}

	void reset(t9::dvar_t* dvar, t9::DvarSetSource source = t9::DvarSetSource::DVAR_SOURCE_INTERNAL);
	void set_dvar_bool(t9::dvar_t* dvar, bool value, t9::DvarSetSource source = t9::DvarSetSource::DVAR_SOURCE_INTERNAL);
	void set_dvar_int(t9::dvar_t* dvar, int value, t9::DvarSetSource source = t9::DvarSetSource::DVAR_SOURCE_INTERNAL);
}
