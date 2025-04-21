#include "scylla/scylla_common.hpp"

#include "scylla/pe_section.hpp"

namespace scylla {
	bool pe_section::highlight_virtual_size() {
		// highlight big virtual sizes -> anti-dump protection
		return (this->virtual_size_ > 0x2000000);
	}
}
