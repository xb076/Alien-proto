workspace "Alien-proto"
	architecture "x64"
	targetdir "build"
	startproject "Editor"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Alien/vendor/GLFW/include"
IncludeDir["Glad"] = "Alien/vendor/Glad/include"
IncludeDir["spdlog"] = "Alien/vendor/spdlog/include"
IncludeDir["ImGui"] = "Alien/vendor/imgui"
IncludeDir["glm"] = "Alien/vendor/glm"
IncludeDir["stb_image"] = "Alien/vendor/stb_image"

include "Alien/vendor/GLFW"
include "Alien/vendor/Glad"
include "Alien/vendor/imgui"

project "Alien"
	location "Alien"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("_bin/" .. outputdir .. "/%{prj.name}" )
	objdir ("_bin-int/" .. outputdir .. "/%{prj.name}" )

	pchheader "pch.h"
	pchsource "Alien/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.spdlog}",
		"%{prj.name}/vendor/assimp/include",
		"%{prj.name}/vendor/stb/include"
	}
	
	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}


	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ALIEN_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
			"ALIEN_BUILD_DLL"

		}

	filter "configurations:Debug"
		defines "ALIEN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ALIEN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ALIEN_DIST"
		runtime "Release"
		optimize "on"


project "Editor"
	location "Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("_bin/" .. outputdir .. "/%{prj.name}")
	objdir ("_bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Alien/vendor/spdlog/include",
		"Alien/src",
		"Alien/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Alien"
	}

	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"ALIEN_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "ALIEN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ALIEN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ALIEN_DIST"
		runtime "Release"
		optimize "on"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("_bin/" .. outputdir .. "/%{prj.name}" )
	objdir ("_bin-int/" .. outputdir .. "/%{prj.name}" )

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Alien/vendor/spdlog/include",
		"Alien/src",
		"Alien/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.Glad}"
	}

	links
	{
		"Alien"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ALIEN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ALIEN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ALIEN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ALIEN_DIST"
		runtime "Release"
		optimize "on"
