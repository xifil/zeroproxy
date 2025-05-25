#include "common.hpp"
#include "game/game.hpp"

#include <memory/signature_store.hpp>
#include <utils/flags.hpp>

#define SETUP_POINTER(name) #name, (void**)&##name
#define SETUP_MOD(mod) [](memory::scanned_result<void> r) { return r.##mod##; }

void game::init() {
	memory::signature_store batch;

	batch.add(SETUP_POINTER(CL_GetLocalClientSignInState), "E8 ? ? ? ? 85 C0 7F ? 8B CB", SETUP_MOD(add(1).rip()));

	if (identification::game::is(iw8_version::v1_46_0_10750827)) {
		batch.add(SETUP_POINTER(Com_GameInfo_GetGameTypeForInternalName), "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 8B 35 ? ? ? ? 33 DB");
	}
	else {
		batch.add(SETUP_POINTER(Com_GameInfo_GetGameTypeForInternalName), "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 8B 35 ? ? ? ? 45 33 DB"
			" 48 8B E9");
	}

	if (identification::game::is(iw8_version::v1_46_0_10750827)) {
		batch.add(SETUP_POINTER(Com_GameInfo_GetMapInfoForLoadName), "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 8B 2D");
	}
	else {
		batch.add(SETUP_POINTER(Com_GameInfo_GetMapInfoForLoadName), "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 8B 3D ? ? ? ? 45 33 DB 48 8B"
			" E9");
	}

	batch.add(SETUP_POINTER(DB_FindXAssetHeader), "E8 ? ? ? ? 44 8B C5 8D 4D", SETUP_MOD(add(1).rip()));

	if (identification::game::is(iw8_version::v1_20_4_7623265_REPLAY, iw8_version::v1_20_4_7623265_SHIP, iw8_version::v1_30_0_8403677)) {
		batch.add(SETUP_POINTER(DB_LoadXFile), "E8 ? ? ? ? 8B F8 44 38 AB", SETUP_MOD(add(1).rip()));
	}
	else if (identification::game::is(iw8_version::v1_38_3_9489393, iw8_version::v1_42_1_10125479, iw8_version::v1_44_0_10435696,
		iw8_version::v1_46_0_10750827))
	{
		batch.add(SETUP_POINTER(DB_LoadXFile), "E8 ? ? ? ? 8B F8 33 ED 40 38 B3", SETUP_MOD(add(1).rip()));
	}

	batch.add(SETUP_POINTER(Dvar_FindVarByName), "E8 ? ? ? ? 48 8B CB 48 63 50", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(Dvar_GetIntSafe), "E8 ? ? ? ? 8B D0 85 C0 75 ? 38 05", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(Dvar_GetStringSafe), "48 83 EC ? E8 ? ? ? ? 8B C8 E8 ? ? ? ? 48 85 C0 75 ? 48 8D 05 ? ? ? ? 48 83 C4 ? C3 80 78");

	batch.add(SETUP_POINTER(Dvar_RegisterBool), "E8 ? ? ? ? 48 8B F0 F6 46", SETUP_MOD(add(1).rip()));

	if (identification::game::is(iw8_version::v1_20_4_7623265_REPLAY, iw8_version::v1_20_4_7623265_SHIP, iw8_version::v1_30_0_8403677,
		iw8_version::v1_38_3_9489393))
	{
		batch.add(SETUP_POINTER(dwGetLogOnStatus), "40 53 48 83 EC ? 48 63 C1 BA");
	}
	else if (identification::game::is(iw8_version::v1_42_1_10125479, iw8_version::v1_44_0_10435696, iw8_version::v1_46_0_10750827)) {
		batch.add(SETUP_POINTER(dwGetLogOnStatus), "40 53 48 83 EC ? 48 63 C1 BA ? ? ? ? 48 69 D8");
	}

	batch.add(SETUP_POINTER(GamerProfile_SetDataByName), "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 8B F1 0F 29 74 24");

	batch.add(SETUP_POINTER(Info_ValueForKey), "48 89 74 24 ? 57 48 83 EC ? 48 8B FA 48 8B F1 48 85 C9 74");

	if (identification::game::is(iw8_version::v1_46_0_10750827)) {
		batch.add(SETUP_POINTER(Live_IsUserSignedInToDemonware), "E8 ? ? ? ? 83 4F ? ? 48 8D 0D", SETUP_MOD(add(1).rip()));
	}
	else {
		batch.add(SETUP_POINTER(Live_IsUserSignedInToDemonware), "E8 ? ? ? ? 84 C0 74 ? 4C 8D 43 ? 8B D7", SETUP_MOD(add(1).rip()));
	}

	batch.add(SETUP_POINTER(lua_pushboolean), "E8 ? ? ? ? EB ? 85 D2 78", SETUP_MOD(add(1).rip()));

	batch.add(SETUP_POINTER(luaL_openlib), "48 89 5C 24 ? 55 56 41 56 48 83 EC ? 48 8B 41");

	if (identification::game::is(iw8_version::v1_20_4_7623265_REPLAY, iw8_version::v1_20_4_7623265_SHIP, iw8_version::v1_30_0_8403677)) {
		batch.add(SETUP_POINTER(R_EndFrame), "48 8B 15 ? ? ? ? 45 33 D2 4C 8B 0D");
	}
	else if (identification::game::is(iw8_version::v1_38_3_9489393, iw8_version::v1_42_1_10125479, iw8_version::v1_44_0_10435696,
		iw8_version::v1_46_0_10750827))
	{
		batch.add(SETUP_POINTER(R_EndFrame), "48 83 EC ? E8 ? ? ? ? 48 8B 15 ? ? ? ? 45 33 D2");
	}

	if (identification::game::is(iw8_version::v1_20_4_7623265_REPLAY, iw8_version::v1_20_4_7623265_SHIP, iw8_version::v1_30_0_8403677)) {
		batch.add(SETUP_POINTER(SEH_StringEd_GetString), "E8 ? ? ? ? 48 8B CB 48 8B F8 E8 ? ? ? ? 48 8B D0 48 8B CF E8 ? ? ? ? 4C 8B 05 ? ? ? ? 48 8D"
			" 0D ? ? ? ? 48 8B D0 E8 ? ? ? ? 48 8B 0D", SETUP_MOD(add(1).rip()));
	}
	else if (identification::game::is(iw8_version::v1_38_3_9489393, iw8_version::v1_42_1_10125479, iw8_version::v1_44_0_10435696)) {
		batch.add(SETUP_POINTER(SEH_StringEd_GetString), "E8 ? ? ? ? 48 8B D0 80 FB", SETUP_MOD(add(1).rip()));
	}
	else if (identification::game::is(iw8_version::v1_46_0_10750827)) {
		// it got inlined on 1.46 lol, localized_strings uses DB_FindXAssetHeader in the abscense of SEH_StringEd_GetString
	}

	if (identification::game::is(iw8_version::v1_20_4_7623265_REPLAY, iw8_version::v1_20_4_7623265_SHIP)) {
		batch.add(SETUP_POINTER(SV_Cmd_Argv), "E8 ? ? ? ? 4C 8B D0 4C 2B D3", SETUP_MOD(add(1).rip()));
	}
	else if (identification::game::is(iw8_version::v1_30_0_8403677, iw8_version::v1_38_3_9489393, iw8_version::v1_42_1_10125479, iw8_version::v1_44_0_10435696)) {
		batch.add(SETUP_POINTER(SV_Cmd_Argv), "E8 ? ? ? ? 48 89 44 24 ? 33 F6 0F", SETUP_MOD(add(1).rip()));
	}
	else if (identification::game::is(iw8_version::v1_46_0_10750827)) {
		batch.add(SETUP_POINTER(SV_Cmd_Argv), "E8 ? ? ? ? 48 8B 1D ? ? ? ? 48 8D 3D ? ? ? ? 48 8B E8", SETUP_MOD(add(1).rip()));
	}

	batch.add(SETUP_POINTER(SV_UpdateUserinfo_f), "40 53 48 83 EC ? 48 8B D9 B9 ? ? ? ? E8 ? ? ? ? 48 8D 8B");

	if (identification::game::is(iw8_version::v1_20_4_7623265_REPLAY, iw8_version::v1_20_4_7623265_SHIP)) {
		batch.add(SETUP_POINTER(unk_IsUnsupportedGPU), "48 83 EC ? 0F B6 05 ? ? ? ? 85 C0 75");
	}

	if (identification::game::is(iw8_version::v1_42_1_10125479, iw8_version::v1_44_0_10435696)) {
		batch.add(SETUP_POINTER(unk_IsUserSignedInToBNet), "40 53 48 83 EC ? 48 8B DA E8 ? ? ? ? 83 38 ? 75 ? E8 ? ? ? ? 84 C0");
	}

	batch.add(SETUP_POINTER(s_isContentEnumerationFinished), "80 3D ? ? ? ? ? 74 ? 48 89 7C 24", SETUP_MOD(add(2).rip().add(1)));
	
	batch.add(SETUP_POINTER(s_luaInFrontend), "0F B6 05 ? ? ? ? 75", SETUP_MOD(add(3).rip()));

	if (identification::game::is(iw8_version::v1_46_0_10750827)) {
		// it doesn't exist anymore?
	}
	else {
		batch.add(SETUP_POINTER(s_presenceData), "48 8D 05 ? ? ? ? 4C 8D 05 ? ? ? ? 48 39 08 74 ? FF C2 48 05", SETUP_MOD(add(3).rip()));
	}

	if (identification::game::is(iw8_version::v1_46_0_10750827)) {
		batch.add(SETUP_POINTER(unk_SignInState), "E8 ? ? ? ? 85 C0 7F ? 8B CB", SETUP_MOD(add(1).rip().add(14).rip()));
	}
	else {
		batch.add(SETUP_POINTER(unk_SignInState), "83 3D ? ? ? ? ? 7E ? 33 C9", SETUP_MOD(add(2).rip().add(1)));
	}

	// 1-game_test -> xenonUserData.m_guardedUserData[0].xuid
	if (identification::game::is(iw8_version::v1_20_4_7623265_REPLAY, iw8_version::v1_20_4_7623265_SHIP)) {
		batch.add(SETUP_POINTER(unk_XUIDCheck1), "48 8D 3D ? ? ? ? 0F 1F 44 00 ? 48 63 C3", SETUP_MOD(add(3).rip()));
	}
	else if (identification::game::is(iw8_version::v1_30_0_8403677, iw8_version::v1_38_3_9489393)) {
		batch.add(SETUP_POINTER(unk_XUIDCheck1), "48 8D 15 ? ? ? ? 48 FF C6 81 FF", SETUP_MOD(add(3).rip()));
	}
	else if (identification::game::is(iw8_version::v1_42_1_10125479, iw8_version::v1_44_0_10435696, iw8_version::v1_46_0_10750827)) {
		batch.add(SETUP_POINTER(unk_XUIDCheck1), "48 8D 1D ? ? ? ? 40 88 35", SETUP_MOD(add(3).rip()));
	}

	if (identification::game::is(iw8_version::v1_20_4_7623265_REPLAY)) {
		batch.add(SETUP_POINTER(unk_XUIDCheck2), "48 8D 0D ? ? ? ? E8 ? ? ? ? 4C 8D 0D ? ? ? ? 48 89 44 24", SETUP_MOD(add(3).rip()));
	}

	batch.add(SETUP_POINTER(unk_BNetClass), "83 3D ? ? ? ? ? 74 ? B8 ? ? ? ? C3", SETUP_MOD(add(2).rip().add(1)));

	batch.scan_all();
}

bool game::is_server() {
	static bool is_server = utils::flags::has_flag("dedicated");
	return is_server;
}
