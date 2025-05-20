#pragma once
#include "common_core.hpp"
#include "utils/nt.hpp"

namespace memory {
	template <typename T>
	class scanned_result {
	public:
		scanned_result(void* pointer)
			: pointer_(pointer)
		{}

		scanned_result(std::uintptr_t pointer)
			: pointer_(reinterpret_cast<void*>(pointer))
		{}

		template <typename S>
		std::enable_if_t<std::is_pointer_v<S>, S> as() {
			return static_cast<S>(this->pointer_);
		}

		template <typename S>
		std::enable_if_t<std::is_lvalue_reference_v<S>, S> as() {
			return *static_cast<std::add_pointer_t<std::remove_reference_t<S>>>(this->pointer_);
		}

		template <typename S>
		std::enable_if_t<std::is_same_v<S, std::uintptr_t>, S> as() {
			return reinterpret_cast<std::uintptr_t>(this->pointer_);
		}

		T* get() {
			return this->as<T*>();
		}

		template <typename S>
		void apply(S** result) {
			*result = static_cast<S*>(this->get());
		}

		template <typename S>
		scanned_result add(S offset) {
			return scanned_result(this->as<std::uintptr_t>() + offset);
		}

		template <typename S>
		scanned_result sub(S offset) {
			return scanned_result(this->as<std::uintptr_t>() - offset);
		}

		scanned_result rip() {
			return this->add(this->as<std::int32_t&>()).add(4);
		}

		scanned_result rel() {
			return scanned_result(*this->as<void**>());
		}

		scanned_result based_rel() {
			return scanned_result(utils::nt::library::get_by_address(this->pointer_).get_ptr()).add(this->as<std::int32_t&>());
		}

		explicit operator bool() {
			return this->pointer_ != nullptr;
		}
	private:
		void* pointer_;
	};
}