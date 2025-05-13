#include "common.hpp"
#include "demonware/byte_buffer.hpp"
#include "demonware/servers/stun_server.hpp"

namespace demonware {
	void stun_server::handle(const endpoint_data& endpoint, const std::string& packet) {
		debug_log_packet("StunServer", packet);

		std::uint8_t type, version, padding;

		byte_buffer buffer(packet);
		buffer.set_use_data_types(false);
		buffer.read_ubyte(&type);
		buffer.read_ubyte(&version);
		buffer.read_ubyte(&padding);

		switch (type) {
		case 30:
			this->ip_discovery(endpoint);
			break;
		case 20:
			this->nat_discovery(endpoint);
			break;
		default:
			break;
		}
	}

	void stun_server::ip_discovery(const endpoint_data& endpoint) {
		const std::uint32_t ip = 0x0100007F;	// 127.0.0.1

		byte_buffer buffer;
		buffer.set_use_data_types(false);
		buffer.write_ubyte(31);		// type
		buffer.write_ubyte(2);		// version
		buffer.write_ubyte(0);		// version
		buffer.write_uint32(ip);	// external ip
		buffer.write_uint16(3074);	// port

		this->send(endpoint, buffer.get_buffer());
	}

	void stun_server::nat_discovery(const endpoint_data& endpoint) {
		const std::uint32_t ip = 0x0100007F;	// 127.0.0.1

		byte_buffer buffer;
		buffer.set_use_data_types(false);
		buffer.write_ubyte(21);						// type
		buffer.write_ubyte(2);						// version
		buffer.write_ubyte(0);						// version
		buffer.write_uint32(ip);					// external ip
		buffer.write_uint16(3074);					// port
		buffer.write_uint32(this->get_address());	// server ip
		buffer.write_uint16(3074);					// server port

		this->send(endpoint, buffer.get_buffer());
	}
}
