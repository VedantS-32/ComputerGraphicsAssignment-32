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
IncludeDir["GLFW"] = "%{wks.location}/vendor/GLFW/include"
IncludeDir["Minimal"] = "%{wks.location}/Minimal/include"

group "Dependencies"
	include "vendor/GLFW"
	include "Minimal"
group ""

group "Assignments"
	include "A1_HelloWorld"
group ""