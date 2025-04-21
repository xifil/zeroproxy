#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/GfxPackedVertex.hpp"
#include "engine/t6/XRigidVertList.hpp"
#include "engine/t6/XSurfaceVertexInfo.hpp"
#include <d3d11.h>

namespace t6 {
	class XSurface {
	public:
		std::uint8_t tile_mode_;		// 0x0000
		std::uint8_t vert_list_count_;	// 0x0001
		std::uint16_t flags_;			// 0x0002
		std::uint16_t vert_count_;		// 0x0004
		std::uint16_t tri_count_;		// 0x0006
		std::uint16_t base_vert_index_;	// 0x0008
	private:
		char pad_000A[0x0002];			// 0x0002
	public:
		std::uint16_t* tri_indices_;	// 0x000C
		XSurfaceVertexInfo vert_info_;	// 0x0010
		GfxPackedVertex* verts0_;		// 0x0020
		ID3D11Buffer* vb0_;				// 0x0024
		union _Verts {
			XRigidVertList* vert_list_;
			XRigidVertList* vert_list_ea_;
		} verts_;						// 0x0028
		ID3D11Buffer* index_buffer_;	// 0x002C
		int part_bits_[5];				// 0x0030
	private:
		char pad_0044[0x000C];			// 0x0044
	};
}
