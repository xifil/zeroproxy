#pragma once
#include "engine/engine_common.hpp"

namespace t9 {
	union DvarLimits {
		struct _enumeration {
			int string_count_;		// 0x0000
			const char** strings_;	// 0x0004
		} enumeration_;
		struct _integer {
			int min_;				// 0x0000
			int max_;				// 0x0004
		} integer_;
		struct _integer64 {
			__int64 min_;			// 0x0000
			__int64 max_;			// 0x0008
		} integer64_;
		struct _value {
			float min_;				// 0x0000
			float max_;				// 0x0004
		} value_;
		struct _vector {
			float min_;				// 0x0000
			float max_;				// 0x0004
		} vector_;
	};
	ENGINE_ASSERT_SZ(DvarLimits, 0x0010);
}
