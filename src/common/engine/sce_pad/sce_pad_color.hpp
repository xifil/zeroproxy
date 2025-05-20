#pragma once
#include "engine/engine_common.hpp"

namespace sce_pad {
	class sce_pad_color {
	public:
		std::uint8_t r_;		// 0x0000
		std::uint8_t g_;		// 0x0001
		std::uint8_t b_;		// 0x0002
	private:
		char pad_0003[0x0001];	// 0x0003
	public:
		sce_pad_color(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b)
			: r_(r)
			, g_(g)
			, b_(b)
		{
			this->pad_0003[0] = 0;
		}

		sce_pad_color(const float r, const float g, const float b)
			: sce_pad_color(static_cast<std::uint8_t>(r * 255.f), static_cast<std::uint8_t>(g * 255.f), static_cast<std::uint8_t>(b * 255.f))
		{}

		sce_pad_color* get_this() {
			return this;
		}
	};
	ENGINE_ASSERT_SZ(sce_pad_color, 0x0004);
}
