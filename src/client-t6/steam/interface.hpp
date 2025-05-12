#pragma once

#ifdef interface
#	undef interface
#endif

namespace steam {
	template <std::size_t ...>
	struct argument_size_calculator final
		: std::integral_constant<std::size_t, 0>
	{};

	template <std::size_t X, std::size_t ... Xs>
	struct argument_size_calculator<X, Xs...> final
		: std::integral_constant<std::size_t, X + ((argument_size_calculator<Xs...>::value + (sizeof(void*) - 1)) & ~(sizeof(void*) - 1))>
	{};
	
	struct raw_steam_id final {
		unsigned int account_id : 32;
		unsigned int account_instance : 20;
		unsigned int account_type : 4;
		int universe : 8;
	};

	typedef union {
		raw_steam_id raw;
		unsigned long long bits;
	} steam_id;

#pragma pack(push, 1)
	struct raw_game_id final {
		unsigned int app_id : 24;
		unsigned int type : 8;
		unsigned int mod_id : 32;
	};

	typedef union {
		raw_game_id raw;
		unsigned long long bits;
	} game_id;
#pragma pack(pop)

	class interface final {
	public:
		class method final {
		public:
			void* pointer = nullptr;
			std::size_t param_size = 0;
		};

		class method_result final {
		public:
			std::string name;
			std::size_t param_size = 0;
			bool name_found = false;
			bool param_size_found = false;
		};

		interface();
		interface(void* interface_ptr);

		operator bool() const;

		template <typename T, typename... Args>
		T invoke(const std::string& method_name, Args ... args) {
			if (!this->interface_ptr_) {
				throw std::runtime_error("Invalid interface pointer");
			}

			const auto method = this->find_method(method_name);
			if (!method.pointer) {
				throw std::runtime_error("Unable to find method: " + method_name);
			}

#			if !defined(_WIN64)
				constexpr std::size_t passed_argc = argument_size_calculator<sizeof(Args)...>::value;
				if (passed_argc != method.param_size) {
					throw std::runtime_error(std::format("Invalid argument count {} [passed_argc] != {} [method.param_size]", passed_argc, method.param_size));
				}
#			endif

			return static_cast<T(__thiscall*)(void*, Args ...)>(method.pointer)(this->interface_ptr_, args...);
		}

		template <typename T, typename... Args>
		T invoke(const std::size_t table_entry, Args ... args) {
			if (!this->interface_ptr_) {
				throw std::runtime_error("Invalid interface pointer");
			}

			return static_cast<T(__thiscall*)(void*, Args ...)>((*this->interface_ptr_)[table_entry])(this->interface_ptr_, args...);
		}

	private:
		void*** interface_ptr_;
		std::unordered_map<std::string, method> methods_;

		method find_method(const std::string& name);
		method search_method(const std::string& name);

		method_result analyze_method(const void* method_ptr);
	};
}
