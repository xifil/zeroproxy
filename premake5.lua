--[[

	ZeroProxy by Lifix
		This project aims to streamline the code of the IW8 and T9 clients to ensure code consistency and ease of access for both,
	as well as providing a solid framework for the clients to run on. This project started development on 04/13/2025, 15:03 PM (+00:00).

	ZeroProxy uses the base software framework used in AlterWare, primarily authored by Maurice Heumann (momo5502) in the now shutdown
	X-Labs Project.

]]--

gitVersioningCommand = "git describe --tags --dirty --always"
gitCurrentBranchCommand = "git symbolic-ref -q --short HEAD"

-- Quote the given string input as a C string
function cstrquote(value)
	if value == nil then
		return "\"\""
	end
	return "\"" .. value:gsub("\\", "\\\\"):gsub("\"", "\\\""):gsub("\n", "\\n"):gsub("\t", "\\t"):gsub("\r", "\\r"):gsub("\a", "\\a"):gsub("\b", "\\b") .. "\""
end

-- Converts tags in "vX.X.X" format and given revision number Y to an array of numbers {X,X,X,Y}.
-- In the case where the format does not work fall back to padding with zeroes and just ending with the revision number.
-- partscount can be either 3 or 4.
function vertonumarr(value, vernumber, partscount)
	vernum = {}
	for num in string.gmatch(value or "", "%d+") do
		if #vernum < 3 then
			table.insert(vernum, tonumber(num))
		end
	end
	while #vernum < 3 do
		table.insert(vernum, 0)
	end
	if #vernum < partscount then
		table.insert(vernum, tonumber(vernumber))
	end
	return vernum
end

dependencies = {
	basePath = "./vendor"
}

function dependencies.load()
	deps = os.matchfiles("premake/*.lua")

	for i, dep in pairs(deps) do
		dep = dep:gsub(".lua", "")
		require(dep)
	end
end

function dependencies.imports()
	for i, proj in pairs(dependencies) do
		if type(i) == 'number' then
			proj.import()
		end
	end
end

function dependencies.projects()
	for i, proj in pairs(dependencies) do
		if type(i) == 'number' then
			proj.project()
		end
	end
end

newoption {
	trigger = "t6-copy-to",
	description = "Optional, copy the Black Ops II DLL to a custom folder after build, define the path here if wanted.",
	value = "PATH"
}

newoption {
	trigger = "iw8-copy-to",
	description = "Optional, copy the Modern Warfare DLL to a custom folder after build, define the path here if wanted.",
	value = "PATH"
}

newoption {
	trigger = "t9-copy-to",
	description = "Optional, copy the Black Ops Cold War DLL to a custom folder after build, define the path here if wanted.",
	value = "PATH"
}

newaction {
	trigger = "version",
	description = "Returns the version string for the current commit of the source code.",
	onWorkspace = function(wks)
		-- get current version via git
		local proc = assert(io.popen(gitVersioningCommand, "r"))
		local gitDescribeOutput = assert(proc:read('*a')):gsub("%s+", "")
		proc:close()
		local version = gitDescribeOutput

		proc = assert(io.popen(gitCurrentBranchCommand, "r"))
		local gitCurrentBranchOutput = assert(proc:read('*a')):gsub("%s+", "")
		local gitCurrentBranchSuccess = proc:close()
		if gitCurrentBranchSuccess then
			-- We got a branch name, check if it is a feature branch
			if gitCurrentBranchOutput ~= "develop" and gitCurrentBranchOutput ~= "master" then
				version = version .. "-" .. gitCurrentBranchOutput
			end
		end

		print(version)
		os.exit(0)
	end
}

newaction {
	trigger = "generate-buildinfo",
	description = "Sets up build information file like version.h.",
	onWorkspace = function(wks)
		-- get old version number from version.hpp if any
		local oldVersion = "(none)"
		local oldVersionHeader = io.open(wks.location .. "/src/generated/version.h", "r")
		if oldVersionHeader ~= nil then
			local oldVersionHeaderContent = assert(oldVersionHeader:read('*l'))
			while oldVersionHeaderContent do
				m = string.match(oldVersionHeaderContent, "#define GIT_DESCRIBE (.+)%s*$")
				if m ~= nil then
						oldVersion = m
				end

				oldVersionHeaderContent = oldVersionHeader:read('*l')
			end
		end

		-- get current version via git
		local proc = assert(io.popen(gitVersioningCommand, "r"))
		local gitDescribeOutput = assert(proc:read('*a')):gsub("%s+", "")
		proc:close()

		-- generate version.hpp with a revision number if not equal
		gitDescribeOutputQuoted = cstrquote(gitDescribeOutput)
		if oldVersion ~= gitDescribeOutputQuoted then
			-- get current git hash and write to version.txt (used by the preliminary updater)
			-- TODO - remove once proper updater and release versioning exists
			local proc = assert(io.popen("git rev-parse HEAD", "r"))
			local gitCommitHash = assert(proc:read('*a')):gsub("%s+", "")
			proc:close()

			-- get whether this is a clean revision (no uncommitted changes)
			proc = assert(io.popen("git status --porcelain", "r"))
			local revDirty = (assert(proc:read('*a')) ~= "")
			if revDirty then revDirty = 1 else revDirty = 0 end
			proc:close()

			-- get current tag name
			proc = assert(io.popen("git describe --tags --abbrev=0"))
			local tagName = proc:read('*l')

			-- get current branch name
			proc = assert(io.popen("git branch --show-current"))
			local branchName = proc:read('*l')

			-- branch for ci
			if branchName == nil or branchName == '' then
				proc = assert(io.popen("git show -s --pretty=%d HEAD"))
				local branchInfo = proc:read('*l')
				m = string.match(branchInfo, ".+,.+, ([^)]+)")
				if m ~= nil then
					branchName = m
				end
			end

			if branchName == nil then
				branchName = "develop"
			end

			print("Detected branch: " .. branchName)

			-- get revision number via git
			local proc = assert(io.popen("git rev-list --count HEAD", "r"))
			local revNumber = assert(proc:read('*a')):gsub("%s+", "")

			print ("Update " .. oldVersion .. " -> " .. gitDescribeOutputQuoted)

			-- write to version.txt for preliminary updater
			-- NOTE - remove this once we have a proper updater and proper release versioning
			local versionFile = assert(io.open(wks.location .. "/src/generated/version.txt", "w"))
			versionFile:write(gitCommitHash)
			versionFile:close()

			-- write version header
			local versionHeader = assert(io.open(wks.location .. "/src/generated/version.h", "w"))
			versionHeader:write("/*\n")
			versionHeader:write(" * Automatically generated by premake5.\n")
			versionHeader:write(" * Do not touch!\n")
			versionHeader:write(" */\n")
			versionHeader:write("\n")
			versionHeader:write("#define GIT_DESCRIBE " .. gitDescribeOutputQuoted .. "\n")
			versionHeader:write("#define GIT_DIRTY " .. revDirty .. "\n")
			versionHeader:write("#define GIT_HASH " .. cstrquote(gitCommitHash) .. "\n")
			versionHeader:write("#define GIT_TAG " .. cstrquote(tagName) .. "\n")
			versionHeader:write("#define GIT_BRANCH " .. cstrquote(branchName) .. "\n")
			versionHeader:write("\n")
			versionHeader:write("// Version transformed for RC files\n")
			versionHeader:write("#define VERSION_PRODUCT_RC " .. table.concat(vertonumarr(tagName, revNumber, 3), ",") .. "\n")
			versionHeader:write("#define VERSION_PRODUCT " .. cstrquote(table.concat(vertonumarr(tagName, revNumber, 3), ".")) .. "\n")
			versionHeader:write("#define VERSION_FILE_RC " .. table.concat(vertonumarr(tagName, revNumber, 4), ",") .. "\n")
			versionHeader:write("#define VERSION_FILE " .. cstrquote(table.concat(vertonumarr(tagName, revNumber, 4), ".")) .. "\n")
			versionHeader:write("\n")
			versionHeader:write("// Alias definitions\n")
			versionHeader:write("#define VERSION GIT_DESCRIBE\n")
			versionHeader:write("#define SHORTVERSION VERSION_PRODUCT\n")
			versionHeader:close()
			local versionHeader = assert(io.open(wks.location .. "/src/generated/version.hpp", "w"))
			versionHeader:write("/*\n")
			versionHeader:write(" * Automatically generated by premake5.\n")
			versionHeader:write(" * Do not touch!\n")
			versionHeader:write(" *\n")
			versionHeader:write(" * This file exists for reasons of complying with our coding standards.\n")
			versionHeader:write(" *\n")
			versionHeader:write(" * The Resource Compiler will ignore any content from C++ header files if they're not from STDInclude.hpp.\n")
			versionHeader:write(" * That's the reason why we now place all version info in version.h instead.\n")
			versionHeader:write(" */\n")
			versionHeader:write("\n")
			versionHeader:write("#include \".\\version.h\"\n")
			versionHeader:close()
		end
	end
}

dependencies.load()

workspace "ZeroProxy"
	--startproject "client"
	startproject "common"
	objdir "%{wks.location}/build/obj"
	targetdir "%{wks.location}/build/%{cfg.platform}/%{cfg.buildcfg}"

	configurations {
		"Debug",
		"Release"
	}

	language "C++"
	cppdialect "C++20"

	platforms { "Win32", "x64" }
	filter "platforms:Win32"
		architecture "x86"
	filter "platforms:x64"
		architecture "x86_64"
	filter {}

	systemversion "latest"
	symbols "On"
	staticruntime "On"
	editandcontinue "Off"
	warnings "Extra"
	characterset "ASCII"

	if os.getenv("CI") then
		defines {
			"CI"
		}
	end

	flags {
		"NoIncrementalLink",
		"NoMinimalRebuild",
		"MultiProcessorCompile",
		"No64BitChecks"
	}

	defines {
		"_DISABLE_CONSTEXPR_MUTEX_CONSTRUCTOR"
	}

	filter "platforms:x64"
		defines {
			"_WINDOWS",
			"WIN32"
		}
	filter {}

	filter "configurations:Release"
		optimize "Size"
		buildoptions {
			"/GL"
		}
		linkoptions {
			"/IGNORE:4702",
			"/LTCG"
		}
		defines {
			"NDEBUG"
		}
	filter {}

	filter "configurations:Debug"
		optimize "Debug"
		defines {
			"DEBUG",
			"_DEBUG"
		}
	filter {}

	project "common"
		location "%{wks.location}/src/%{prj.name}"
		kind "StaticLib"
		language "C++"

		files {
			"./src/common/**.hpp",
			"./src/common/**.cpp"
		}

		includedirs {
			"./src/common",
			"./src/generated"
		}

		resincludedirs {
			"$(ProjectDir)src"
		}

		prebuildcommands {
			"cd ../../ && .\\tools\\premake\\premake5.exe generate-buildinfo"
		}

		dependencies.imports()

	project "client-t6"
		location "%{wks.location}/src/%{prj.name}"
		objdir "%{wks.location}/build/obj/t6"
		targetdir "%{wks.location}/build/%{cfg.platform}/%{cfg.buildcfg}/t6"
		kind "SharedLib"
		language "C++"

		targetname "d3d11"

		pchheader "common.hpp"
		pchsource "src/%{prj.name}/common.cpp"

		files {
			"./src/%{prj.name}/**.rc",
			"./src/%{prj.name}/**.hpp",
			"./src/%{prj.name}/**.cpp",
			"./src/%{prj.name}/resources/**.*"
		}

		includedirs {
			"./src/%{prj.name}",
			"./src/common",
			"./src/generated"
		}

		resincludedirs {
			"./src/generated"
		}

		links {
			"common"
		}

		if _OPTIONS["t6-copy-to"] then
			postbuildcommands {
				"copy /y \"$(TargetPath)\" \"" .. _OPTIONS["t6-copy-to"] .. "\""
			}
		end

		dependencies.imports()

	project "client-iw8"
		location "%{wks.location}/src/%{prj.name}"
		objdir "%{wks.location}/build/obj/iw8"
		targetdir "%{wks.location}/build/%{cfg.platform}/%{cfg.buildcfg}/iw8"
		kind "SharedLib"
		language "C++"

		targetname "version"

		pchheader "common.hpp"
		pchsource "src/%{prj.name}/common.cpp"

		files {
			"./src/%{prj.name}/**.rc",
			"./src/%{prj.name}/**.hpp",
			"./src/%{prj.name}/**.cpp",
			"./src/%{prj.name}/resources/**.*"
		}

		includedirs {
			"./src/%{prj.name}",
			"./src/common",
			"./src/generated"
		}

		resincludedirs {
			"./src/generated"
		}

		links {
			"common"
		}

		if _OPTIONS["iw8-copy-to"] then
			postbuildcommands {
				"copy /y \"$(TargetPath)\" \"" .. _OPTIONS["iw8-copy-to"] .. "\""
			}
		end

		dependencies.imports()

	project "client-t9"
		location "%{wks.location}/src/%{prj.name}"
		objdir "%{wks.location}/build/obj/t9"
		targetdir "%{wks.location}/build/%{cfg.platform}/%{cfg.buildcfg}/t9"
		kind "SharedLib"
		language "C++"

		targetname "version"

		pchheader "common.hpp"
		pchsource "src/%{prj.name}/common.cpp"

		files {
			"./src/%{prj.name}/**.rc",
			"./src/%{prj.name}/**.hpp",
			"./src/%{prj.name}/**.cpp",
			"./src/%{prj.name}/resources/**.*"
		}

		includedirs {
			"./src/%{prj.name}",
			"./src/common",
			"./src/generated"
		}

		resincludedirs {
			"./src/generated"
		}

		links {
			"common"
		}

		if _OPTIONS["t9-copy-to"] then
			postbuildcommands {
				"copy /y \"$(TargetPath)\" \"" .. _OPTIONS["t9-copy-to"] .. "\""
			}
		end

		dependencies.imports()

	group "Dependencies"
		dependencies.projects()
