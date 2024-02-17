workspace "ComputerGraphicsAssignments-32"
	architecture "x64"
	startproject "Sandbox"

	configurations {
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root directory
IncludeDir = {}
IncludeDir["Minimal"] = "%{wks.location}/Minimal/include"
IncludeDir["GLFW"] = "%{wks.location}/vendor/GLFW/include"
IncludeDir["GLAD"] = "%{wks.location}/vendor/GLAD/include"
IncludeDir["glm"] = "%{wks.location}/vendor/glm"
IncludeDir["ImGui"] = "%{wks.location}/vendor/ImGui"
IncludeDir["stb_image"] = "%{wks.location}/vendor/stb_image"
IncludeDir["tiny_obj_loader"] = "%{wks.location}/vendor/tiny_obj_loader"
IncludeDir["assimp"] = "%{wks.location}/vendor/assimp/include"

group "Dependencies"
	include "Minimal"
	include "vendor/GLFW"
	include "vendor/GLAD"
	include "vendor/ImGui"
	include "vendor/stb_image"
	include "vendor/tiny_obj_loader"
	include "vendor/assimp"
group ""

group "Assignments"
	include "A1_HelloWorld"
	include "A2_Transformations"
group ""