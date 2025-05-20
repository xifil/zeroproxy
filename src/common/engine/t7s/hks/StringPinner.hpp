#pragma once
#include "engine/engine_common.hpp"

namespace t7s::hks {
	class StringPinner {
	public:
		class Node {
		public:
			InternString* strings_[0x20];	// 0x0000
			Node* prev_;					// 0x0100
		};
		ENGINE_ASSERT_SZ(Node, 0x0108);

		lua_State* const state_;			// 0x0000
		StringPinner* const prev_;			// 0x0008
		InternString** next_strings_place_;	// 0x0010
		Node first_node_;					// 0x0018
		Node* current_node_;				// 0x0120
	};
	ENGINE_ASSERT_SZ(StringPinner, 0x0128);
}
