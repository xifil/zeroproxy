#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	enum class MaterialStageConfig : std::int8_t {
		MTL_STANDARD_STAGES = 0,
		MTL_TESSELLATION_STAGES = 1,
		MTL_STAGE_CONFIG_COUNT = 2
	};
}
