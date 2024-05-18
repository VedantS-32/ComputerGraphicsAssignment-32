project "A2_Transformations"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .."/%{prj.name}")
	objdir ("bin-int/" .. outputdir .."/%{prj.name}")

	files {
		"%{wks.location}/vendor/stb_image/**.h",
		"%{wks.location}/vendor/stb_image/**.cpp",
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		"%{IncludeDir.Minimal}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.assimp}"
	}

	links
	{
		"glfw",
		"glad",
		"ImGui",
		"assimp",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
		runtime "debug"
		symbols "On"

	filter "configurations:Release"
		runtime "release"
		optimize "On"