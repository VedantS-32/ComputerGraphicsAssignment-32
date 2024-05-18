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
IncludeDir["glfw"] = "%{wks.location}/vendor/glfw/include"
IncludeDir["glad"] = "%{wks.location}/vendor/glad/include"
IncludeDir["glm"] = "%{wks.location}/vendor/glm"
IncludeDir["ImGui"] = "%{wks.location}/vendor/ImGui"
IncludeDir["stb_image"] = "%{wks.location}/vendor/stb_image"
IncludeDir["assimp"] = "%{wks.location}/vendor/assimp/include"

group "Dependencies"
	include "Minimal"
	include "vendor/glfw"
	include "vendor/glad"
	include "vendor/ImGui"
	include "vendor/assimp"
group ""

group "Assignments"
	include "A1_HelloWorld"
	include "A2_Transformations"
group ""