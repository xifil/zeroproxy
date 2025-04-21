stb = {
	source = path.join(dependencies.basePath, "stb")
}

function stb.import()
	stb.includes()
end

function stb.includes()
	includedirs {
		stb.source
	}
end

function stb.project()
    -- STB is include only
end

table.insert(dependencies, stb)
