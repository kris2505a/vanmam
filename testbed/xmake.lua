target("testbed")
    set_kind("binary")

    add_files("src/**.cpp")
    add_headerfiles("src/**.h")

    add_includedirs("src")

    add_deps("engine")
  
    add_defines("PROJECT_NAME=\"testbed\"")

    set_targetdir("$(projectdir)/bin/$(mode)")
    set_objectdir("$(projectdir)/obj/$(mode)/$(name)")
