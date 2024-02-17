project "A2_Transformations"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .."/%{prj.name}")
	objdir ("bin-int/" .. outputdir .."/%{prj.name}")

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
		"%{IncludeDir.assimp}",
		-- "%{IncludeDir.tiny_obj_loader}"
		-- "vendor/assimp/.",
		-- "vendor/assimp/code",
		-- "vendor/assimp/include",
		-- "vendor/assimp/contrib/irrXML",
		-- "vendor/assimp/contrib/pugixml/src",
		-- "vendor/assimp/contrib/zlib",
		-- "vendor/assimp/contrib/rapidjson/include",
		-- "vendor/assimp/contrib",
		-- "vendor/assimp/contrib/utf8cpp/source",
		-- "vendor/assimp/contrib/zip/src",
		-- "vendor/assimp/contrib/unzip"
	}
	


	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"stb_image",
		"assimp",
		-- "tiny_obj_loader",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "off"
		systemversion "latest"
	
	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"