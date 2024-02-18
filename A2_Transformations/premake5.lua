project "A2_Transformations"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .."/%{prj.name}")
	objdir ("bin-int/" .. outputdir .."/%{prj.name}")

	postbuildcommands {
		("{COPYFILE} ../vendor/assimp/bin/Release/assimp-vc143-mt.dll ./bin/" .. outputdir .. "/%{prj.name}")
	}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		"%{IncludeDir.Minimal}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.assimp}"
	}

	libdirs {
		"%{LibDir.assimpr}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"stb_image",
		"assimp-vc143-mt",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "off"
		systemversion "latest"
	
	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"