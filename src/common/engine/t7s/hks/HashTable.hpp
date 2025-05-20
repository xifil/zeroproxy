#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/ChunkHeader.hpp"
#include "engine/t7s/hks/Object.hpp"

namespace t7s::hks {
	class HashTable : public ChunkHeader {
	public:
		class Node {
		public:
			Object key_;	// 0x0000
			Object value_;	// 0x0010
		};
		ENGINE_ASSERT_SZ(Node, 0x0020);

		Metatable* meta_;			// 0x0010
		std::uint32_t mask_;		// 0x0018
	private:
		char pad_001C[0x0004];		// 0x001C
	public:
		Node* hash_part_;			// 0x0020
		Object* array_part_;		// 0x0028
		std::uint32_t array_size_;	// 0x0030
	private:
		char pad_0034[0x0004];		// 0x0034
	public:
		Node* free_node_;			// 0x0038
	};
	ENGINE_ASSERT_SZ(HashTable, 0x0040);
}
