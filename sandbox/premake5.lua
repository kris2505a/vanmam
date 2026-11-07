project "sandbox"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++20"

  targetdir("%{wks.location}/bin/" .. outputdir .. "/")
  objdir("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

  defines {
	  "PROJECT_NAME=\"sandbox\""
  }

  files {
	  "src/**.h",
	  "src/**.cpp"
  }

  includedirs {
	  "src/",
	  public_includes["engine"]
  }

  links {
	  "engine"
  }

  filter "system:windows"
	defines "PF_WINDOWS"
  
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