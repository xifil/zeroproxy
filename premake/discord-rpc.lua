discordrpc = {
	source = path.join(dependencies.basePath, "discord-rpc")
}

function discordrpc.import()
	links {
	    "discord-rpc"
	}
	discordrpc.includes()
end

function discordrpc.includes()
	includedirs {
		discordrpc.source
	}
end

function discordrpc.project()
	project "discord-rpc"
		location "%{wks.location}/premake/out"
		language "C++"

		discordrpc.includes()
		rapidjson.import()

		files {
			path.join(discordrpc.source, "*.h"),
			path.join(discordrpc.source, "*.cpp")
		}

		removefiles {
			path.join(discordrpc.source, "dllmain.cpp"),
			path.join(discordrpc.source, "*_linux.cpp"),
			path.join(discordrpc.source, "*_unix.cpp"),
			path.join(discordrpc.source, "*_osx.cpp")
		}

		warnings "Off"
		kind "StaticLib"
end

table.insert(dependencies, discordrpc)
