#include "common.hpp"
#include "game/game.hpp"

#include <memory/signature_store.hpp>
#include <utils/flags.hpp>

#define SETUP_POINTER(name) #name, (void**)&##name
#define SETUP_MOD(mod) [](memory::scanned_result<void> r) { return r.##mod##; }

void game::init() {
	memory::signature_store batch;

	batch.add(SETUP_POINTER(bdLogMessage), "4C 8B DC 55 41 54 41 55 41 56 41 57");

	batch.add(SETUP_POINTER(Cinematic_StartPlayback), "E8 ? ? ? ? 44 0F B6 05", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(CL_GetKeyBindingInternal), "E8 ? ? ? ? 8B F8 4C 8B BC 24", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(Com_Frame_Try_Block_Function), "E8 ? ? ? ? FF 05 ? ? ? ? C7 44 24 ? ? ? ? ? C6 44 24", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(Com_PrintMessage), "40 53 41 54 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24");

	batch.add(SETUP_POINTER(Content_HasEntitlementOwnershipByRef), "48 89 5C 24 ? 57 48 83 EC ? 48 8B FA 48 85 D2");

	batch.add(SETUP_POINTER(Content_GetAvailableContentPacks), "48 89 5C 24 ? 57 48 83 EC ? 0F B6 F9");

	batch.add(SETUP_POINTER(Content_DoWeHaveContentPack), "40 53 48 83 EC ? 48 85 C9 74");

	batch.add(SETUP_POINTER(CScrCmd_SetAllControllersLightbarColor), "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 0F 29 74 24 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89"
		" 44 24 ? 8B 3D");

	batch.add(SETUP_POINTER(DB_FindXAssetHeader), "E8 ? ? ? ? 4C 8B 70", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(FS_FindXZone), "E8 ? ? ? ? 48 85 C0 48 8D 2D", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(GPad_ResetLightbarColor), "E8 ? ? ? ? 48 83 EB ? 75 ? 48 8B 4C 24", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(GPad_SetLightbarColor), "E8 ? ? ? ? EB ? E8 ? ? ? ? 48 83 EB", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(hks_obj_tolstring), "40 53 57 41 56 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 4C 8B F1 49 8B D8");

	batch.add(SETUP_POINTER(hksI_openlib), "40 53 56 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 49 8B F0 48 8B FA 48 8B D9 48 85 D2");

	batch.add(SETUP_POINTER(Key_KeynumToString), "48 89 5C 24 ? 57 48 83 EC ? 48 63 DA 41 8B F8 83 FB");

	batch.add(SETUP_POINTER(lua_pcall), "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 48 8B 69");

	batch.add(SETUP_POINTER(lua_pushlstring), "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? BF");

	batch.add(SETUP_POINTER(lua_pushvfstring), "48 89 5C 24 ? 55 56 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 49 8B D8 48 8B FA");

	batch.add(SETUP_POINTER(lua_setfield), "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B D9 49 8B F8 48 8B 49");

	batch.add(SETUP_POINTER(lua_toboolean), "E8 ? ? ? ? 41 83 FA", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(lua_topointer), "4C 8B C1 81 FA ? ? ? ? 7E ? 85 D2 7E ? 48 8B 49 ? 48 83 C1 ? 48 63 D2 48 C1 E2 ? 48 03 CA 49 3B 48 ? 73 ? E9");

	batch.add(SETUP_POINTER(MSStore_OwnsContent), "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 48 8B F1 E8");

	batch.add(SETUP_POINTER(R_AddCmdDrawTextWithCursorInternal), "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC ? 80 39");

	batch.add(SETUP_POINTER(Scr_GetInt), "E8 ? ? ? ? 85 C0 40 0F 95 C6 C7 44 24", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(SND_EndFrame), "40 53 56 57 48 83 EC ? 48 8D 35");

	batch.add(SETUP_POINTER(unk_AC_OnDllLoaded), "83 F9 ? 0F 85 ? ? ? ? 48 81 EC");
	
	batch.add(SETUP_POINTER(unk_AC_Unk2_Threaded), "4C 8D 05 ? ? ? ? 33 D2 33 C9 41 FF D2", SETUP_MOD(add(3).rip()));

	batch.add(SETUP_POINTER(unk_AC_Unk3), "48 8D 0D ? ? ? ? 41 FF D0", SETUP_MOD(add(3).rip()));

	batch.add(SETUP_POINTER(unk_AC_Unk4), "48 8D 15 ? ? ? ? 45 33 C0 41 FF D1 FF 05", SETUP_MOD(add(3).rip()));

	batch.add(SETUP_POINTER(unk_AC_Unk5), "48 8D 15 ? ? ? ? 45 33 C0 41 FF D1 4C 8B 05", SETUP_MOD(add(3).rip()));

	batch.add(SETUP_POINTER(unk_AC_Unk6), "E8 ? ? ? ? BB ? ? ? ? 41 FF C5", SETUP_MOD(add(1).rip()));
	
	batch.add(SETUP_POINTER(unk_AC_Unk7), "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B"
		" E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? B8 ? ? ? ? B9 ? ? ? ? 41 BD");
	
	batch.add(SETUP_POINTER(unk_AC_Unk8), "4C 8D 05 ? ? ? ? BA ? ? ? ? 33 C9 41 FF D2 49 89 45 ? FF 15 ? ? ? ? 48 63 C8 4C 69 C1 ? ? ? ? 49 BE",
		SETUP_MOD(add(3).rip()));
	
	batch.add(SETUP_POINTER(unk_AC_Unk10), "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B"
		" E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? B8 ? ? ? ? B9 ? ? ? ? 0F B7 55");
	
	batch.add(SETUP_POINTER(unk_AC_Unk11), "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B"
		" E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? B8 ? ? ? ? B9 ? ? ? ? 44 0F B7 75");

	batch.add(SETUP_POINTER(unk_AC_Unk13_Threaded), "4C 8D 05 ? ? ? ? BA ? ? ? ? 33 C9 41 FF D2 48 89 05", SETUP_MOD(add(3).rip()));

	batch.add(SETUP_POINTER(unk_InitSysDvars), "E8 ? ? ? ? 8B FB 66 90", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(unk_WaitForObjects), "40 53 48 83 EC ? 48 8D 4C 24 ? FF 15 ? ? ? ? 48 8B 0D");

	batch.add(SETUP_POINTER(clientGameStates), "43 8B 84 81", SETUP_MOD(add(4).based_rel()));

	batch.add(SETUP_POINTER(com_quitInProgress), "83 3D ? ? ? ? ? 75 ? B1", SETUP_MOD(add(2).rip()));

	batch.add(SETUP_POINTER(s_contentPackMetaData), "8B 9C CF ? ? ? ? B1", SETUP_MOD(add(3).rip()));

	batch.add(SETUP_POINTER(s_gamePads), "48 8D 15 ? ? ? ? 85 FF", SETUP_MOD(add(3).rip()));

	batch.add(SETUP_POINTER(unk_AC_State), "48 85 05", SETUP_MOD(add(3).rip()));

	batch.add(SETUP_POINTER(unk_KeyNumToName), "4C 8D 05 ? ? ? ? 33 C9 49 8B C0 48 8D 15 ? ? ? ? 39 18", SETUP_MOD(add(3).rip()));

	batch.add(SETUP_POINTER(unk_OwnedContent), "48 8D 0D ? ? ? ? 86 04 0A", SETUP_MOD(add(3).rip()));

	batch.add(SETUP_POINTER(unk_PadHandles), "41 83 BC 2E ? ? ? ? ? 7C", SETUP_MOD(add(4).based_rel()));

	batch.add(SETUP_POINTER(unk_WatermarkFont), "48 8D 05 ? ? ? ? 48 89 05 ? ? ? ? 48 8D 05 ? ? ? ? EB ? 48 8D 05", SETUP_MOD(add(3).rip()));

	batch.scan_all(true);
}

bool game::is_server() {
	static bool is_server = utils::flags::has_flag("dedicated");
	return is_server;
}

bool game::should_enable_demonware_emulator() {
	static bool should_enable_demonware_emulator = utils::flags::has_flag("dw");
	return should_enable_demonware_emulator;
}

int game::Com_LocalClient_GetControllerIndex(int local_client_num) {
	if (local_client_num >= 0 && local_client_num <= 2 && clientGameStates[local_client_num].local_client_num_ == local_client_num) {
		return clientGameStates[local_client_num].controller_index_;
	}

	return -1;
}

void game::lua_pop(t7s::lua_State* s, int n) {
	s->api_stack_.top_ -= n;
}

void game::lua_pushboolean(t7s::lua_State* s, int b) {
	auto top = s->api_stack_.top_;
	top->v_.boolean_ = b;
	top->t_ = ENUM_UNDER(t7s::hks::ObjectType::TBOOLEAN);
	s->api_stack_.top_ = top + 1;
}

void game::lua_pushinteger(t7s::lua_State* s, int n) {
	auto top = s->api_stack_.top_;
	top->v_.number_ = static_cast<float>(n);
	top->t_ = ENUM_UNDER(t7s::hks::ObjectType::TNUMBER);
	s->api_stack_.top_ = top + 1;
}

void game::lua_pushnil(t7s::lua_State* s) {
	auto top = s->api_stack_.top_;
	top->v_.number_ = 0;
	top->t_ = ENUM_UNDER(t7s::hks::ObjectType::TNIL);
	s->api_stack_.top_ = top + 1;
}

void game::lua_pushnumber(t7s::lua_State* s, float n) {
	auto top = s->api_stack_.top_;
	top->v_.number_ = n;
	top->t_ = ENUM_UNDER(t7s::hks::ObjectType::TNUMBER);
	s->api_stack_.top_ = top + 1;
}

void game::lua_pushfstring(t7s::lua_State* s, const char* fmt, ...) {
	va_list va;
	va_start(va, fmt);
	lua_pushvfstring(s, fmt, &va);
}

void game::lua_pushvalue(t7s::lua_State* s, int index) {
	t7s::hks::Object* st;
	auto object = extra::get_object_for_index(s, index);
	st = s->api_stack_.top_;
	*st = object;
	s->api_stack_.top_ = st + 1;
}

void game::lua_setglobal(t7s::lua_State* s, const char* k) {
	lua_setfield(s, LUA_GLOBALSINDEX, k);
}

const char* game::lua_tostring(t7s::lua_State* s, int index) {
	auto object = extra::get_object_for_index(s, index);
	return hks_obj_tolstring(s, &object, 0);
}

float game::lua_tonumber(t7s::lua_State* s, int index) {
	auto object = extra::get_object_for_index(s, index);
	return object.v_.number_;
}

void game::luaL_register(t7s::lua_State* s, const char* lib_name, const t7s::luaL_Reg* l) {
	hksI_openlib(s, lib_name, l, 0, 1);
}

t7s::hks::Object game::extra::get_object_for_index(t7s::lua_State* s, int index) {
	float result;
	t7s::hks::Object* object = nullptr;
	int failure;

	if (index <= LUA_REGISTRYINDEX) {
		failure = 0;
		switch (index) {
		case LUA_REGISTRYINDEX:
			object = &s->global_->registry_;
			break;
		case LUA_GLOBALSINDEX:
			object = &s->globals_;
			break;
		case LUA_ENVIRONINDEX:
			s->c_env_.v_.c_closure_ = (t7s::hks::CClosure*)s->api_stack_.base_[-1].v_.c_closure_->env_;
			s->c_env_.t_ = ENUM_UNDER(t7s::hks::ObjectType::TTABLE);
			object = &s->c_env_;
			break;
		default:
			object = (t7s::hks::Object*)(&s->api_stack_.base_[-1].v_.c_closure_->num_upvalues_ + 8 * (LUA_GLOBALSINDEX - index));
			break;
		}
	}
	else if (index <= 0) {
		if (index == 0) {
			failure = 1;
		}
		else if (&s->api_stack_.top_[index] < s->api_stack_.base_) {
			failure = 1;
		}
		else {
			failure = 0;
			object = &s->api_stack_.top_[index];
		}
	}
	else if (&s->api_stack_.base_[index - 1] >= s->api_stack_.top_) {
		failure = 1;
	}
	else {
		failure = 0;
		object = &s->api_stack_.base_[index - 1];
	}

	if (object != nullptr) {
		return *object;
	}

	t7s::hks::Object object_tmp;
	object_tmp.t_ = 0;
	object_tmp.v_.ptr_ = nullptr;
	return object_tmp;
}
