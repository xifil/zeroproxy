﻿#pragma once

namespace steam_proxy {
	const utils::nt::library& get_overlay_module();
	const char* get_player_name();

	void initialize();
}
