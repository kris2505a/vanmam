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

  for _, dir in ipairs(os.matchdirs("src/*")) do
	if os.isfile(dir .. "/premake5.lua") then
	  include(dir)
	end
  end

  filter "system:windows"
	defines {
		"PF_WINDOWS",
		"WIN32_LEAN_AND_MEAN",
		"NOMINMAX"
	}
	links {
		"d3d11",
		"dxgi",
		"d3dcompiler"
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