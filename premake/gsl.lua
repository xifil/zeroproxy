gsl = {
	source = path.join(dependencies.basePath, "GSL")
}

function gsl.import()
	gsl.includes()
end

function gsl.includes()
	includedirs {
		path.join(gsl.source, "include")
	}
end

function gsl.project()
    -- GSL is include only
end

table.insert(dependencies, gsl)
