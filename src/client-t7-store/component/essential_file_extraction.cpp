#include "common.hpp"

#include <loader/component_loader.hpp>
#include <utils/binary_resource.hpp>
#include <utils/io.hpp>

#include "resource.h"

/*
 * this component is only really useful for individuals who chose to use this client with their steam folder.
 * this is because the game will throw an access violation and refuse to load if it doesn't find "MicrosoftGame.config",
 * so why not give it everything?
 */

namespace essential_file_extraction {
	namespace {
		std::map<int, std::string> files_to_extract = {
			{ WS_FOLDER_appxmanifest_xml, "appxmanifest.xml" },
			{ WS_FOLDER_game_icn, "game.icn" },
			{ WS_FOLDER_gamelaunchhelper_exe, "gamelaunchhelper.exe" },
			{ WS_FOLDER_GraphicsLogo_png, "GraphicsLogo.png" },
			{ WS_FOLDER_LargeLogo_png, "LargeLogo.png" },
			{ WS_FOLDER_layout_5a9fecfa_103a_9983_67f4_587e8ee42a6a_xml, "layout_5a9fecfa-103a-9983-67f4-587e8ee42a6a.xml" },
			{ WS_FOLDER_localization_en_txt, "localization_en.txt" },
			{ WS_FOLDER_MicrosoftGame_config, "MicrosoftGame.config" },
			{ WS_FOLDER_Party_dll, "Party.dll" },
			{ WS_FOLDER_PartyXboxLive_dll, "PartyXboxLive.dll" },
			{ WS_FOLDER_PlayFabMultiplayerGDK_dll, "PlayFabMultiplayerGDK.dll" },
			{ WS_FOLDER_resources_pri, "resources.pri" },
			{ WS_FOLDER_SmallLogo_png, "SmallLogo.png" },
			{ WS_FOLDER_SplashScreen_png, "SplashScreen.png" },
			{ WS_FOLDER_StoreLogo_png, "StoreLogo.png" }
		};
	}

	struct component final : generic_component {
		void post_load() override {
			for (const auto& [id, name] : files_to_extract) {
				if (std::filesystem::exists(name)) {
					continue;
				}

				utils::binary_resource resource(id, name);
				utils::io::write_file(name, resource.get_data());

				LOG("Component/Extraction", INFO, "Extracted Windows Store file \"{}\".", name);
			}
		}
	};
}

REGISTER_COMPONENT(essential_file_extraction::component)
