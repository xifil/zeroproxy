#include "common.hpp"
#include "steam.hpp"

#include <utils/hook.hpp>
#include <utils/io.hpp>
#include <utils/nt.hpp>

#include "component/steam_proxy.hpp"

namespace steam {
	uint64_t callbacks::call_id_ = 0;
	std::recursive_mutex callbacks::mutex_;
	std::map<uint64_t, bool> callbacks::calls_;
	std::map<uint64_t, callbacks::base*> callbacks::result_handlers_;
	std::vector<callbacks::result> callbacks::results_;
	std::vector<callbacks::base*> callbacks::callback_list_;

	uint64_t callbacks::register_call() {
		std::lock_guard<std::recursive_mutex> _(mutex_);
		calls_[++call_id_] = false;
		return call_id_;
	}

	void callbacks::register_callback(base* handler, const int callback) {
		std::lock_guard<std::recursive_mutex> _(mutex_);
		handler->set_i_callback(callback);
		callback_list_.push_back(handler);
	}

	void callbacks::unregister_callback(base* handler) {
		std::lock_guard<std::recursive_mutex> _(mutex_);
		for (auto i = callback_list_.begin(); i != callback_list_.end();) {
			if (*i == handler) {
				i = callback_list_.erase(i);
			}
			else {
				++i;
			}
		}
	}

	void callbacks::register_call_result(const uint64_t call, base* result) {
		std::lock_guard<std::recursive_mutex> _(mutex_);
		result_handlers_[call] = result;
	}

	void callbacks::unregister_call_result(const uint64_t call, base* /*result*/) {
		std::lock_guard<std::recursive_mutex> _(mutex_);
		const auto i = result_handlers_.find(call);
		if (i != result_handlers_.end()) {
			result_handlers_.erase(i);
		}
	}

	void callbacks::return_call(void* data, const int size, const int type, const uint64_t call) {
		std::lock_guard<std::recursive_mutex> _(mutex_);

		result result{};
		result.call = call;
		result.data = data;
		result.size = size;
		result.type = type;

		calls_[call] = true;

		results_.emplace_back(result);
	}

	void callbacks::run_callbacks() {
		std::lock_guard<std::recursive_mutex> _(mutex_);

		for (const auto& result : results_) {
			if (result_handlers_.find(result.call) != result_handlers_.end()) {
				result_handlers_[result.call]->run(result.data, false, result.call);
			}

			for (const auto& callback : callback_list_) {
				if (callback && callback->get_i_callback() == result.type) {
					callback->run(result.data, false, 0);
				}
			}

			if (result.data) {
				free(result.data);
			}
		}

		results_.clear();
	}

	void patch_iat_entry(const std::string& name, void* new_entry) {
		static ::utils::nt::library game{};
		auto entry = game.get_iat_entry("steam_api.dll", name);
		if (entry != nullptr) {
			::utils::hook::set(entry, new_entry);
		}
	}

	void patch_iat_entries() {
#		define PATCH_ENTRY(name) patch_iat_entry(#name, name)
		PATCH_ENTRY(SteamAPI_RestartAppIfNecessary);
		PATCH_ENTRY(SteamAPI_Init);
		PATCH_ENTRY(SteamAPI_RegisterCallResult);
		PATCH_ENTRY(SteamAPI_RegisterCallback);
		PATCH_ENTRY(SteamAPI_RunCallbacks);
		PATCH_ENTRY(SteamAPI_Shutdown);
		PATCH_ENTRY(SteamAPI_UnregisterCallResult);
		PATCH_ENTRY(SteamAPI_UnregisterCallback);
		PATCH_ENTRY(SteamAPI_GetSteamInstallPath);
		PATCH_ENTRY(SteamGameServer_GetHSteamPipe);
		PATCH_ENTRY(SteamGameServer_GetHSteamUser);
		PATCH_ENTRY(SteamAPI_GetHSteamUser);
		PATCH_ENTRY(SteamAPI_GetHSteamPipe);
		PATCH_ENTRY(SteamInternal_CreateInterface);
		PATCH_ENTRY(SteamInternal_GameServer_Init);
		PATCH_ENTRY(SteamGameServer_Init);
		PATCH_ENTRY(SteamGameServer_RunCallbacks);
		PATCH_ENTRY(SteamGameServer_Shutdown);
		PATCH_ENTRY(SteamFriends);
		PATCH_ENTRY(SteamMatchmaking);
		PATCH_ENTRY(SteamGameServer);
		PATCH_ENTRY(SteamNetworking);
		PATCH_ENTRY(SteamRemoteStorage);
		PATCH_ENTRY(SteamUser);
		PATCH_ENTRY(SteamUtils);
		PATCH_ENTRY(SteamApps);
		PATCH_ENTRY(SteamUserStats);
#		undef PATCH_ENTRY
	}

#	define ANNOUNCE_CALL() ;//LOG("SteamProxy", DEBUG, __FUNCTION__ " called."); Sleep(1000);

	bool SteamAPI_RestartAppIfNecessary() {
		ANNOUNCE_CALL();
		return false;
	}

	bool SteamAPI_Init() {
		ANNOUNCE_CALL();
		const std::filesystem::path steam_path = SteamAPI_GetSteamInstallPath();
		if (steam_path.empty()) {
			return true;
		}

		::utils::nt::library::load(steam_path / "tier0_s.dll");
		::utils::nt::library::load(steam_path / "vstdlib_s.dll");
		::utils::nt::library::load(steam_path / "gameoverlayrenderer.dll");
		::utils::nt::library::load(steam_path / "steamclient.dll");

		steam_proxy::initialize();

		return true;
	}

	void SteamAPI_RegisterCallResult(callbacks::base* result, const uint64_t call) {
		ANNOUNCE_CALL();
		callbacks::register_call_result(call, result);
	}

	void SteamAPI_RegisterCallback(callbacks::base* handler, const int callback) {
		ANNOUNCE_CALL();
		callbacks::register_callback(handler, callback);
	}

	void SteamAPI_RunCallbacks() {
		ANNOUNCE_CALL();
		callbacks::run_callbacks();
	}

	void SteamAPI_Shutdown() {
		ANNOUNCE_CALL();
	}

	void SteamAPI_UnregisterCallResult(callbacks::base* result, const uint64_t call) {
		ANNOUNCE_CALL();
		callbacks::unregister_call_result(call, result);
	}

	void SteamAPI_UnregisterCallback(callbacks::base* handler) {
		ANNOUNCE_CALL();
		callbacks::unregister_callback(handler);
	}

	const char* SteamAPI_GetSteamInstallPath() {
		ANNOUNCE_CALL();
		static std::string install_path{};
		if (!install_path.empty()) {
			return install_path.data();
		}

		HKEY reg_key;
		if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software\\WOW6432Node\\Valve\\Steam", 0, KEY_QUERY_VALUE, &reg_key) == ERROR_SUCCESS) {
			char path[MAX_PATH] = { 0 };
			DWORD length = sizeof(path);
			RegQueryValueExA(reg_key, "InstallPath", nullptr, nullptr, reinterpret_cast<BYTE*>(path), &length);
			RegCloseKey(reg_key);

			install_path = path;
		}

		return install_path.data();
	}

	void* SteamGameServer_GetHSteamPipe() {
		ANNOUNCE_CALL();
		return reinterpret_cast<void*>(1);
	}

	void* SteamGameServer_GetHSteamUser() {
		ANNOUNCE_CALL();
		return reinterpret_cast<void*>(1);
	}

	void* SteamAPI_GetHSteamUser() {
		ANNOUNCE_CALL();
		return reinterpret_cast<void*>(1);
	}

	void* SteamAPI_GetHSteamPipe() {
		ANNOUNCE_CALL();
		return reinterpret_cast<void*>(1);
	}

	void* SteamInternal_CreateInterface(const char* interface_name) {
		ANNOUNCE_CALL();
		if (std::string(interface_name) == "SteamClient012") {
			static client c;
			return &c;
		}

		return nullptr;
	}

	bool SteamInternal_GameServer_Init() {
		ANNOUNCE_CALL();
		return true;
	}

	bool SteamGameServer_Init() {
		ANNOUNCE_CALL();
		return true;
	}

	void SteamGameServer_RunCallbacks() {
		ANNOUNCE_CALL();
	}

	void SteamGameServer_Shutdown() {
		ANNOUNCE_CALL();
	}

	friends* SteamFriends() {
		ANNOUNCE_CALL();
		static friends friends;
		return &friends;
	}

	matchmaking* SteamMatchmaking() {
		ANNOUNCE_CALL();
		static matchmaking matchmaking;
		return &matchmaking;
	}

	void* SteamGameServer() {
		ANNOUNCE_CALL();
		return new void*;
	}

	networking* SteamNetworking() {
		ANNOUNCE_CALL();
		static networking networking;
		return &networking;
	}

	remote_storage* SteamRemoteStorage() {
		ANNOUNCE_CALL();
		static remote_storage remote_storage;
		return &remote_storage;
	}

	user* SteamUser() {
		ANNOUNCE_CALL();
		static user user;
		return &user;
	}

	utils* SteamUtils() {
		ANNOUNCE_CALL();
		static utils utils;
		return &utils;
	}

	apps* SteamApps() {
		ANNOUNCE_CALL();
		static apps apps;
		return &apps;
	}

	user_stats* SteamUserStats() {
		ANNOUNCE_CALL();
		static user_stats user_stats;
		return &user_stats;
	}
}