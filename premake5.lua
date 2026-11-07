workspace "vanmam"
  architecture "x64"
  startproject "sandbox"

  configurations {
	  "Debug",
	  "Release"
  }

  public_includes = {}

  public_includes["engine"] = "%{wks.location}/engine/src/"

  outputdir = "%{cfg.architecture}-%{cfg.buildcfg}"

  include "engine"
  include "sandbox"
