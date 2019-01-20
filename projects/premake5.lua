newoption({
	trigger = "gmcommon",
	description = "Sets the path to the garrysmod_common (https://github.com/danielga/garrysmod_common) directory",
	value = "path to garrysmod_common directory"
})

local gmcommon = _OPTIONS.gmcommon or os.getenv("GARRYSMOD_COMMON")
if gmcommon == nil then
	error("you didn't provide a path to your garrysmod_common (https://github.com/danielga/garrysmod_common) directory")
end

include(gmcommon)

CreateWorkspace({name = "floodgate", allow_debug = false})
	filter("system:macosx")
		buildoptions("-mmacosx-version-min=10.5")
		linkoptions("-mmacosx-version-min=10.5")

	CreateProject({serverside = true})
		warnings("Default")
		IncludeSDKCommon()
		IncludeSDKTier0()