#include "common.hpp"
#include "demonware/servers/auth3_server.hpp"

#include <utils/cryptography.hpp>
#include <utils/string.hpp>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

namespace demonware {
	namespace {
#pragma pack(push, 1)
		struct auth_ticket {
			std::uint32_t magic_number_;
			char type_;
			std::uint32_t title_id_;
			std::uint32_t time_issued_;
			std::uint32_t time_expires_;
			std::uint64_t license_id_;
			std::uint64_t user_id_;
			char username_[64];
			char session_key_[24];
			char using_hash_magic_number_[3];
			char hash_[4];
		};
#pragma pack(pop)
	}

	void auth3_server::send_reply(reply* data) {
		if (!data) {
			return;
		}

		this->send(data->data());
	}

	void auth3_server::handle(const std::string& packet) {
		LOG("Demonware/Auth3", DEBUG, "[DW]: [auth]: {}", packet);
		if (packet.starts_with("POST /auth/")) {
			LOG("Demonware/Auth3", DEBUG, "[DW]: [auth]: user requested authentication.");
			return;
		}

		/*unsigned int title_id = 0;
		unsigned int iv_seed = 0;
		std::string identity{};
		std::string session_token{};
		std::string account_token{};

		rapidjson::Document j;
		j.Parse(packet.data(), packet.size());

		if (j.HasMember("title_id") && j["title_id"].IsString()) {
			title_id = std::stoul(j["title_id"].GetString());
		}

		if (j.HasMember("iv_seed") && j["iv_seed"].IsString()) {
			iv_seed = std::stoul(j["iv_seed"].GetString());
		}

		if (j.HasMember("identity") && j["identity"].IsString()) {
			identity = j["identity"].GetString();
		}

		if (j.HasMember("extra_data") && j["extra_data"].IsString()) {
			rapidjson::Document extra_data;
			auto& ed = j["extra_data"];
			extra_data.Parse(ed.GetString(), ed.GetStringLength());

			if (extra_data.HasMember("session_token") && extra_data["session_token"].IsString()) {
				auto& token_field = extra_data["session_token"];
				std::string token_b64(token_field.GetString(), token_field.GetStringLength());
				session_token = token_b64;
			}

			if (extra_data.HasMember("account_token") && extra_data["account_token"].IsString()) {
				auto& token_field = extra_data["account_token"];
				std::string token_b64(token_field.GetString(), token_field.GetStringLength());
				account_token = utils::cryptography::base64::decode(token_b64);
			}
		}

		std::string session_key("\x13\x37\x13\x37\x13\x37\x13\x37\x13\x37\x13\x37\x13\x37\x13\x37\x13\x37\x13\x37\x13\x37\x13\x37", 24);

		// client_ticket
		auth_ticket ticket{};
		std::memset(&ticket, 0x0, sizeof ticket);
		ticket.magic_number_ = 0xEFBDADDE;
		ticket.type_ = 0;
		ticket.title_id_ = title_id;
		ticket.time_issued_ = static_cast<std::uint32_t>(time(nullptr));
		ticket.time_expires_ = ticket.time_issued_ + 30000;
		ticket.license_id_ = 0;
		ticket.user_id_ = 0;
		strncpy_s(ticket.username_, sizeof(ticket.username_), session_token.data(), session_token.length());
		std::memcpy(ticket.session_key_, session_key.data(), 24);

		const auto client_ticket_b64 = utils::cryptography::base64::encode(reinterpret_cast<const unsigned char*>(&ticket), sizeof(ticket));

		// server_ticket
		std::uint8_t server_ticket[128];
		std::memset(&server_ticket, 0, sizeof server_ticket);
		std::memcpy(server_ticket, session_key.data(), 24);
		const auto server_ticket_b64 = utils::cryptography::base64::encode(server_ticket, 128);

		// from keys.hpp
		//demonware::set_session_key(session_key);

		// header time
		char date[64];
		const auto now = time(nullptr);
		tm gmtm{};
		gmtime_s(&gmtm, &now);
		strftime(date, 64, "%a, %d %b %G %T", &gmtm);

		rapidjson::Document extra;
		extra.SetObject();

		std::string username = std::string(ticket.username_, sizeof(ticket.username_)).data();
		extra.AddMember("username", username, extra.GetAllocator());
		extra.AddMember("time_to_live", 9999, extra.GetAllocator());

		const auto lul = utils::cryptography::base64::encode("lul");
		extra.AddMember("extended_data", lul, extra.GetAllocator());

		rapidjson::StringBuffer extra_buffer{};
		rapidjson::Writer<rapidjson::StringBuffer, rapidjson::Document::EncodingType, rapidjson::ASCII<>> extra_writer(extra_buffer);
		extra.Accept(extra_writer);

		std::string extra_data{};
		extra_data.append(extra_buffer.GetString(), extra_buffer.GetSize());
		// json content
		rapidjson::Document doc;
		doc.SetObject();

		doc.AddMember("auth_task", "85", doc.GetAllocator());
		doc.AddMember("code", "700", doc.GetAllocator());

		auto seed = std::to_string(iv_seed);
		doc.AddMember("iv_seed", seed, doc.GetAllocator());
		doc.AddMember("client_ticket", client_ticket_b64, doc.GetAllocator());
		doc.AddMember("server_ticket", server_ticket_b64, doc.GetAllocator());
		doc.AddMember("client_id", "treyarch-cod-t8-bnet", doc.GetAllocator());
		doc.AddMember("account_type", "bnet", doc.GetAllocator());
		doc.AddMember("crossplay_enabled", false, doc.GetAllocator());
		doc.AddMember("loginqueue_eanbled", false, doc.GetAllocator());
		doc.AddMember("identity", identity, doc.GetAllocator());
		doc.AddMember("extra_data", extra_data, doc.GetAllocator());
		doc.AddMember("service_level", "paid", doc.GetAllocator());

		rapidjson::Value value{};
		doc.AddMember("lsg_endpoint", value, doc.GetAllocator());

		rapidjson::StringBuffer buffer{};
		rapidjson::Writer<rapidjson::StringBuffer, rapidjson::Document::EncodingType, rapidjson::ASCII<>>
			writer(buffer);
		doc.Accept(writer);

		// http stuff
		std::string result;
		result.append("HTTP/1.1 200 OK\r\n");
		result.append("Server: TornadoServer/4.5.3\r\n");
		result.append("Content-Type: application/json\r\n");
		result.append(utils::string::va("Date: %s GMT\r\n", date));
		result.append(utils::string::va("Content-Length: %d\r\n\r\n", buffer.GetSize()));
		result.append(buffer.GetString(), buffer.GetSize());

		raw_reply reply(result);

		this->send_reply(&reply);

		LOG("Demonware/Auth3", DEBUG, "[DW]: [auth]: user successfully authenticated.");*/
	}
}