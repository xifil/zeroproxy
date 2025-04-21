rapidjson = {
	source = path.join(dependencies.basePath, "rapidjson")
}

function rapidjson.import()
	rapidjson.includes()
end

function rapidjson.includes()
	includedirs {
		path.join(rapidjson.source, "include")
	}

	defines {
		"RAPIDJSON_HAS_STDSTRING"
	}
end

function rapidjson.project()
	-- rapidjson is include only
end

table.insert(dependencies, rapidjson)
