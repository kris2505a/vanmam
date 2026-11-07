project "engine"
  kind "SharedLib"
  language "C++"
  cppdialect "C++20"

  targetdir("%{wks.location}/bin/" .. outputdir .. "/")
  objdir("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

  defines {
	  "PROJECT_NAME=\"vanmam\"",
	  "VM_SHARED_BUILD"
  }

  includedirs {
	  "src/"
  }

  include "src/core"
  include "src/platform"

  filter "system:windows"
	defines "PF_WINDOWS"
	links {
		"d3d12",
		"dxgi",
		"dxguid"
	}
  
  filter "system:linux"
    defines "PF_LINUX"

  filter "configurations:Debug"
    defines "VM_DEBUG"
	runtime "Debug"
	symbols "on"


  filter "configurations:Release"
    defines "VM_RELEASE"
	runtime "Release"
	optimize "on"

  filter {}