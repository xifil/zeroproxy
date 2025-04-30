#include "common.hpp"
#include "game/dvars.hpp"
#include "game/game.hpp"

namespace dvars {
	namespace {
		bool is_dvar_ptr_valid(t9::dvar_t* dvar) {
			return dvar != nullptr && (dvar->name_hash_ & 0x7FFFFFFFFFFFFFFF) != 0;
		}
	}

	t9::dvar_t* get_dvar_by_hash(std::int64_t hash) {
		return game::Dvar_FindVar(hash);
	}

	void reset(t9::dvar_t* dvar, t9::DvarSetSource source) {
		if (!is_dvar_ptr_valid(dvar)) {
			return;
		}
		game::Dvar_Reset(dvar, source);
	}

	void set_dvar_bool(t9::dvar_t* dvar, bool value, t9::DvarSetSource source) {
		if (!is_dvar_ptr_valid(dvar)) {
			return;
		}
		game::Dvar_SetBoolFromSource(dvar, value, source);
	}

	void set_dvar_int(t9::dvar_t* dvar, int value, t9::DvarSetSource source) {
		if (!is_dvar_ptr_valid(dvar)) {
			return;
		}
		game::Dvar_SetIntFromSource(dvar, value, source);
	}
}
