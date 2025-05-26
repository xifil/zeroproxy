#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/lua_State.hpp"

namespace iw8 {
	template <typename T>
	class LUIMethod {
	public:
		union {
			const char* name_;		// 0x0000
			std::uint64_t hash_;	// 0x0000
		};
		int (*func_)(lua_State* s);	// 0x0008
		LUIMethod<T>* next_;		// 0x0010

		const char* get_name(std::uint64_t* ptr_to_encryption_key) {
			static utils::nt::library game{};

			if (game.is_address_in_range(this->hash_)) {
				return this->name_;
			}

			if (ptr_to_encryption_key != nullptr) {
				std::uint64_t decrypted_ptr = *ptr_to_encryption_key ^ this->hash_;
				if (game.is_address_in_range(decrypted_ptr)) {
					return PTR_AS(const char*, decrypted_ptr);
				}
			}

			return nullptr;
		}
	};
	ENGINE_ASSERT_SZ(LUIMethod<void>, 0x0018);
}
