target("sandbox")
    set_kind("binary")

    add_files("src/**.cpp")
    add_headerfiles("src/**.h")

    add_includedirs("src")

    add_deps("engine")
  
    add_defines("PROJECT_NAME=\"testbed\"")

    if is_plat("linux") then
      add_defines("PF_LINUX")
    elseif is_plat("windows") then
      add_defines("PF_WINDOWS")
    end
    set_targetdir("$(projectdir)/bin/$(mode)")
    set_objectdir("$(projectdir)/obj/$(mode)/$(name)")
