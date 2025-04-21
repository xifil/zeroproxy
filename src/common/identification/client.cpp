#include "identification/client.hpp"

extern "C" const char* ext_get_client_name();

namespace identification::client {
	const char* get_client_name() {
		return ext_get_client_name();
	}
}
