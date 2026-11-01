-- 1. Include subdirectories outside of the target definition
includes("src/core")
includes("src/platform")
includes("deps/glfw")

-- 2. Define the engine target
target("engine")
    set_kind("shared")

    -- Depend on the GLFW target defined inside deps/glfw/xmake.lua
    -- This handles target ordering, include inheritance, and library paths automatically.
    add_deps("GLFW")

    add_includedirs("src", {public = true})

    -- Defines
    add_defines("VM_SHARE_BUILD", "PROJECT_NAME=\"vanmam\"")

    if is_mode("debug") then
        add_defines("VM_DEBUG")
    elseif is_mode("release") then
        add_defines("VM_RELEASE")
    end

    if is_plat("linux") then 
        add_defines("VM_PLATFORM_LINUX")
    end

    -- Output directories
    set_targetdir("$(projectdir)/bin/$(mode)")
    set_objectdir("$(projectdir)/obj/$(mode)/$(name)")
