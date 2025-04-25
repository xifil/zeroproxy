#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	union DvarLimits {
		struct _enumeration {
			int string_count_;		// 0x0000
		private:
			char pad_0004[0x0004];	// 0x0004
		public:
			const char** strings_;	// 0x0008
		} enumeration_;
		struct _integer {
			int min_;				// 0x0000
			int max_;				// 0x0004
		} integer_;
		struct _integer64 {
			std::int64_t min_;		// 0x0000
			std::int64_t max_;		// 0x0008
		} integer64_;
		struct _unsigned_int64 {
			std::uint64_t min_;		// 0x0000
			std::uint64_t max_;		// 0x0008
		} unsigned_int64_;
		struct _value {
			float min_;				// 0x0000
			float max_;				// 0x0004
			float dev_gui_step_;	// 0x0008
		} value_;
		struct _vector {
			float min_;				// 0x0000
			float max_;				// 0x0004
			float dev_gui_step_;	// 0x0008
		} vector_;
	};
	ENGINE_ASSERT_SZ(DvarLimits, 0x0010);
}
