#pragma once
#include "common_core.hpp"
#include "utils/nt.hpp"

namespace identification::game {
	const char* get_target_game();
	
	namespace mode {
		inline constexpr std::uint32_t AIO = 0;
		inline constexpr std::uint32_t MP = 1;
		inline constexpr std::uint32_t SP = 2;
		inline constexpr std::uint32_t ZM = 3;
	}
	
	namespace version {
		namespace iw4_store {
			inline constexpr std::uint32_t v2_0_6_MP = 0x67C8EE3F;
			inline constexpr std::uint32_t v2_0_6_SP = 0x67C8EE56;
		}

		namespace iw5 {
			inline constexpr std::uint32_t v1_9_388110_SP = 0x22886E14;
			inline constexpr std::uint32_t v1_9_388110_MP = 0x1FE1222A;
		}

		namespace t6 {
			inline constexpr std::uint32_t v1_0_12_1468705_SP = 1468705;
			inline constexpr std::uint32_t v1_0_39_1656332_ZM = 1656332;
			inline constexpr std::uint32_t v1_0_41_1902371_ZM = 1902371;
			inline constexpr std::uint32_t v1_0_44_1759941_MP = 1759941;
			inline constexpr std::uint32_t v1_0_45_1898228_MP = 1898228;
		}

		namespace t6_store {
			inline constexpr std::uint32_t v2_0_0_43_MP = 0x67E407AA;
			inline constexpr std::uint32_t v2_0_0_43_SP = 0x67E40777;
			inline constexpr std::uint32_t v2_0_0_43_ZM = 0x67E40101;
		}

		namespace iw6_store {
			inline constexpr std::uint32_t v3_15_11_SP = 0x67C9BDB7;
			inline constexpr std::uint32_t v3_15_11_MP = 0x67C9BDB9;
		}

		namespace t7_store {
			inline constexpr std::uint32_t v2_0_0 = 0x67363F2A;
		}

		namespace s2_store {
			inline constexpr std::uint32_t v2_0_0_SP = 0xAFD962C3;
			inline constexpr std::uint32_t v2_0_0_MP = 0xF8D1963C;
		}
		
		namespace iw8 {
			inline constexpr std::uint32_t v0_01_2_7089334 = 0x37CCF2A5;
			inline constexpr std::uint32_t v1_03_0_7209368 = 0x641EA3EB;
			inline constexpr std::uint32_t v1_20_4_7623265_REPLAY = 0xFF380251;
			inline constexpr std::uint32_t v1_20_4_7623265_SHIP = 0x6E9C74C8;
			inline constexpr std::uint32_t v1_30_0_8403677 = 0x7E37B0B9;
			inline constexpr std::uint32_t v1_38_3_9489393 = 0xCE698CA4;
			inline constexpr std::uint32_t v1_42_1_10125479 = 0x54FBBFD1;
			inline constexpr std::uint32_t v1_44_0_10435696 = 0xD6C4C029;
			inline constexpr std::uint32_t v1_46_0_10750827 = 0x5910A608;
		}
		
		namespace t9 {
			inline constexpr std::uint32_t v1_34_0_15931218 = 0x64CD0B8C;
			inline constexpr std::uint32_t v1_34_1_15931218 = 0x645C43F8;
		}

		class identifier {
		public:
			identifier(std::uint32_t checksum, const std::string& game, const std::string& version, std::uint32_t mode = mode::AIO)
				: checksum_(checksum)
				, game_(game)
				, version_(version)
				, mode_(mode)
			{}

			const std::uint32_t checksum_;
			const std::string game_;
			const std::string version_;
			const std::uint32_t mode_;

			std::string get_full_display_name(bool include_version = true, bool include_optional_mode = true) const {
				std::string version = "";
				if (include_version) {
					version = std::format(" v{}", this->version_);
				}
				std::string optional_mode = "";
				if (include_optional_mode && this->mode_ != mode::AIO) {
					std::string optional_mode_name;
					switch (this->mode_) {
					case mode::MP:
						optional_mode_name = "Multiplayer";
						break;
					case mode::SP:
						optional_mode_name = "Singleplayer";
						break;
					case mode::ZM:
						optional_mode_name = "Zombies";
						break;
					default:
						optional_mode_name = "Unknown";
						break;
					}
					optional_mode = std::format(" ({})", optional_mode_name);
				}
				return std::format("Call of Duty: {}{}{}", this->game_, version, optional_mode);
			}

			operator std::uint32_t() const {
				return this->checksum_;
			}
		};
	}

	std::uint32_t get_checksum();
	
	inline std::vector<version::identifier> version_list = {
		{ version::iw4_store::v2_0_6_MP, "Modern Warfare 2", "2.0.6", mode::MP },
		{ version::iw4_store::v2_0_6_SP, "Modern Warfare 2", "2.0.6", mode::SP },
		{ version::iw5::v1_9_388110_SP, "Modern Warfare 3", "1.9.388110", mode::SP },
		{ version::iw5::v1_9_388110_MP, "Modern Warfare 3", "1.9.388110", mode::MP },
		{ version::t6::v1_0_12_1468705_SP, "Black Ops II", "1.0.12.1468705", mode::SP },
		{ version::t6::v1_0_39_1656332_ZM, "Black Ops II", "1.0.39.1656332", mode::ZM },
		{ version::t6::v1_0_41_1902371_ZM, "Black Ops II", "1.0.41.1902371", mode::ZM },
		{ version::t6::v1_0_44_1759941_MP, "Black Ops II", "1.0.44.1759941", mode::MP },
		{ version::t6::v1_0_45_1898228_MP, "Black Ops II", "1.0.45.1898228", mode::MP },
		{ version::t6_store::v2_0_0_43_MP, "Black Ops II", "2.0.0.43", mode::MP },
		{ version::t6_store::v2_0_0_43_SP, "Black Ops II", "2.0.0.43", mode::SP },
		{ version::t6_store::v2_0_0_43_ZM, "Black Ops II", "2.0.0.43", mode::ZM },
		{ version::iw6_store::v3_15_11_MP, "Ghosts", "3.15.11", mode::MP },
		{ version::iw6_store::v3_15_11_SP, "Ghosts", "3.15.11", mode::SP },
		{ version::t7_store::v2_0_0, "Black Ops III", "2.0.0" },
		{ version::s2_store::v2_0_0_MP, "WWII", "2.0.0", mode::MP },
		{ version::s2_store::v2_0_0_SP, "WWII", "2.0.0", mode::SP },
		{ version::iw8::v0_01_2_7089334, "Modern Warfare", "0.01.2.7089334" },
		{ version::iw8::v1_03_0_7209368, "Modern Warfare", "1.03.0.7209368" },
		{ version::iw8::v1_20_4_7623265_REPLAY, "Modern Warfare", "1.20.4.7623265-replay" },
		{ version::iw8::v1_20_4_7623265_SHIP, "Modern Warfare", "1.20.4.7623265-ship" },
		{ version::iw8::v1_30_0_8403677, "Modern Warfare", "1.30.0.8403677" },
		{ version::iw8::v1_38_3_9489393, "Modern Warfare", "1.38.3.9489393" },
		{ version::iw8::v1_42_1_10125479, "Modern Warfare", "1.42.1.10125479" },
		{ version::iw8::v1_44_0_10435696, "Modern Warfare", "1.44.0.10435696" },
		{ version::iw8::v1_46_0_10750827, "Modern Warfare", "1.46.0.10750827" },
		{ version::t9::v1_34_0_15931218, "Black Ops Cold War", "1.34.0.15931218" },
		{ version::t9::v1_34_1_15931218, "Black Ops Cold War", "1.34.1.15931218" }
	};

	inline version::identifier get_version() {
		static const auto get_version_internal = [] {
			std::uint32_t checksum = get_checksum();
			auto it = std::ranges::find_if(version_list, [checksum](const version::identifier& i) {
				return i == checksum;
			});
			
			if (it != version_list.end() && it._Unwrapped() != nullptr) {
				return *it._Unwrapped();
			}

			return version::identifier(checksum, std::format("Unknown-{:08X}", checksum), "0.0.0.0");
		}();
		return get_version_internal;
	}

	inline bool is_game(const std::string& game) {
		return get_version().game_ == game;
	}

	template <typename... Args>
	bool is(Args... args) {
		std::uint32_t checksum = get_version();
		return ((args == checksum) || ...);
	}
}

namespace iw4_store_version = identification::game::version::iw4_store;
namespace iw5_version = identification::game::version::iw5;
namespace t6_version = identification::game::version::t6;
namespace t6_store_version = identification::game::version::t6_store;
namespace iw6_store_version = identification::game::version::iw6_store;
namespace t7_store_version = identification::game::version::t7_store;
namespace s2_store_version = identification::game::version::s2_store;
namespace iw8_version = identification::game::version::iw8;
namespace t9_version = identification::game::version::t9;
