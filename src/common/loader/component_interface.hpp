﻿#pragma once

enum class component_priority {
	lua_hook = -1,
	min = 0,
	name,
	steam_proxy,
	arxan,
	call_spoofer,
	pointers
};

enum class component_type {
	client,
	server,
	any
};

struct generic_component {
	static constexpr component_type type = component_type::any;

	virtual ~generic_component() = default;

	virtual void post_load() {}
	virtual void pre_destroy() {}
	virtual void post_unpack() {}

	virtual component_priority priority() const {
		return component_priority::min;
	}
};

struct client_component : generic_component {
	static constexpr component_type type = component_type::client;
};

struct server_component : generic_component {
	static constexpr component_type type = component_type::server;
};
