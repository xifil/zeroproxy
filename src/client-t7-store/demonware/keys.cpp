#include "common.hpp"
#include "demonware/keys.hpp"

#include <utils/cryptography.hpp>
#include <utils/string.hpp>

#include "resource.h"

#define TRY_EXPERIMENTAL_SESSION_KEY true

namespace demonware {
	struct data_t {
		char session_key[24];
		char response[8];
		char hmac_key[20];
		char enc_key[16];
		char dec_key[16];
	} data{};

	std::string packet_buffer;

	void calculate_hmacs(const char* data_, const std::uint32_t data_size, const char* key, const std::uint32_t key_size, char* dst,
		const std::uint32_t dst_size)
	{
		char buffer[512];
		std::uint32_t pos = 0;
		std::uint32_t out_offset = 0;
		char count = 1;
		std::string result;

		// buffer add key
		std::memcpy(&buffer[pos], key, key_size);
		pos += key_size;

		// buffer add count
		buffer[pos] = count;
		pos++;

		// calculate hmac
		result = utils::cryptography::hmac_sha1::compute(std::string(buffer, pos), std::string(data_, data_size));

		// save output
		std::memcpy(dst, result.data(), std::min(20u, (dst_size - out_offset)));
		out_offset = 20;

		// second loop
		while (true) {
			// if we filled the output buffer, exit
			if (out_offset >= dst_size) {
				break;
			}

			// buffer add last result
			pos = 0;
			std::memcpy(&buffer[pos], result.data(), 20);
			pos += 20;

			// buffer add key
			std::memcpy(&buffer[pos], key, key_size);
			pos += key_size;

			// buffer add count
			count++;
			buffer[pos] = count;
			pos++;

			// calculate hmac
			result = utils::cryptography::hmac_sha1::compute(std::string(buffer, pos), std::string(data_, data_size));

			// save output
			std::memcpy(dst + out_offset, result.data(), std::min(20u, (dst_size - out_offset)));
			out_offset += 20;
		}
	}

	void derive_keys_s1() {
		const auto packet_hash = utils::cryptography::sha1::compute(packet_buffer);

#		if TRY_EXPERIMENTAL_SESSION_KEY
			std::string bd_auth_traffic_signing_key = utils::nt::load_resource(DW_AUTH_TRAFFIC_SIGNING_KEY);

			char out_1[24];
			calculate_hmacs(data.session_key, 24, bd_auth_traffic_signing_key.data(), 294, out_1, 24);

			auto data_3 = utils::cryptography::hmac_sha1::compute(std::string(out_1, 24), packet_hash);
#		else
			auto data_3 = utils::cryptography::hmac_sha1::compute(data.session_key, packet_hash);
#		endif

		char out_2[16];
		calculate_hmacs(data_3.data(), 20, "CLIENTCHAL", 10, out_2, 16);

		char out_3[72];
		calculate_hmacs(data_3.data(), 20, "BDDATA", 6, out_3, 72);

		std::memcpy(data.response, &out_2[8], 8);
		std::memcpy(data.hmac_key, &out_3[20], 20);
		std::memcpy(data.dec_key, &out_3[40], 16);
		std::memcpy(data.enc_key, &out_3[56], 16);

		LOG("Demonware/Keys", DEBUG, "[DW] Response id: {}", utils::string::dump_hex(std::string(&out_2[8], 8)).data());
		LOG("Demonware/Keys", DEBUG, "[DW] Hash verify: {}", utils::string::dump_hex(std::string(&out_3[20], 20)).data());
		LOG("Demonware/Keys", DEBUG, "[DW] AES dec key: {}", utils::string::dump_hex(std::string(&out_3[40], 16)).data());
		LOG("Demonware/Keys", DEBUG, "[DW] AES enc key: {}", utils::string::dump_hex(std::string(&out_3[56], 16)).data());
		LOG("Demonware/Keys", DEBUG, "[DW] Bravo 6, going dark.");
	}

	void queue_packet_to_hash(const std::string& packet) {
		packet_buffer.append(packet);
	}

	void set_session_key(const std::string& key) {
		std::memcpy(data.session_key, key.data(), 24);
	}

	std::string get_decrypt_key() {
		return std::string(data.dec_key, 16);
	}

	std::string get_encrypt_key() {
		return std::string(data.enc_key, 16);
	}

	std::string get_hmac_key() {
		return std::string(data.hmac_key, 20);
	}

	std::string get_response_id() {
		return std::string(data.response, 8);
	}
}
