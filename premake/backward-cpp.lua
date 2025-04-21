backwardcpp = {
	source = path.join(dependencies.basePath, "backward-cpp")
}

function backwardcpp.import()
	links {
	    "backward-cpp"
	}
	backwardcpp.includes()
end

function backwardcpp.includes()
	includedirs {
		backwardcpp.source
	}

	defines {
		"NOMINMAX"
	}
end

function backwardcpp.project()
	project "backward-cpp"
		location "%{wks.location}/premake/out"
		language "C++"

		backwardcpp.includes()

		files {
			path.join(backwardcpp.source, "backward.cpp"),
			path.join(backwardcpp.source, "backward.hpp")
		}

		warnings "Off"
		kind "StaticLib"
end

table.insert(dependencies, backwardcpp)
