#pragma once
#include "common_core.hpp"
#include "memory/memory.hpp"
#include "utils/concurrency.hpp"

#include "logger/logger.hpp"

namespace memory {
	class signature_store {
		using res = scanned_result<void>;
		
		class signature {
		public:
			signature(const utils::nt::library& library, const std::string& name, void** pointer, const std::string& pattern, std::function<res(res)> mod)
				: library_(library)
				, name_(name)
				, pattern_(pattern)
				, pointer_(pointer)
				, mod_(std::move(mod))
			{}

			void scan() const {
				if (*this->pointer_ != nullptr) {
					return;
				}
				
				res sc_temp = sig_scan(this->library_, this->pattern_, this->name_);
				if (sc_temp.as<void*>() != nullptr) {
					sc_temp = this->mod_(sc_temp);
					*this->pointer_ = sc_temp.as<void*>();
				}
			}

			utils::nt::library library_;
			std::string name_;
			std::string pattern_;
			void** pointer_;
			std::function<res(res)> mod_;
		};
	public:
		signature_store(const utils::nt::library& library)
			: library_(library)
		{}

		signature_store()
			: signature_store(utils::nt::library())
		{}
	
		void add(const std::string& name, void** pointer, const std::string& pattern, std::function<res(res)> mod) {
			this->signatures_.push_back(signature(this->library_, name, pointer, pattern, std::move(mod)));
		}
		
		void add(const std::string& name, void** ptr, const std::string& pattern) {
			this->signatures_.push_back(signature(this->library_, name, ptr, pattern, [](res r) { return r; }));
		}

		void scan_all(bool run_sync = false) {
			if (run_sync) {
				for (auto& sig : this->signatures_) {
					sig.scan();
				}
			}
			else {
				utils::concurrency::async_for_each<signature>(this->signatures_, [](auto& sig) {
					sig.scan();
				});
			}
		}
	private:
		utils::nt::library library_;
		std::vector<signature> signatures_{};
	};
}