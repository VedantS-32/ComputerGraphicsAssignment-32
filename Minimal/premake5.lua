project "Minimal"
	kind "Utility"
	language "C++"

	targetdir ("bin/" .. outputdir .."/%{prj.name}")
	objdir ("bin-int/" .. outputdir .."/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp",
		"include/**.h",
		"include/**.cpp"
	}

	includedirs {
		"src",
		"include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
	
	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"