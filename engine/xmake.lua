-- 1. Include subdirectories outside of the target definition
includes("src/core")
includes("src/platform")
includes("src/event")
includes("src/render_hw")

-- 2. Define the engine target
target("engine")
    set_kind("shared")

    -- Depend on the GLFW target defined inside deps/glfw/xmake.lua
    -- This handles target ordering, include inheritance, and library paths automatically.

    add_includedirs("src", {public = true})

    -- Defines
    add_defines("VM_SHARED_BUILD", "PROJECT_NAME=\"vanmam\"")

    add_defines("UNICODE", "_UNICODE")

    if is_mode("debug") then
        add_defines("VM_DEBUG")
    elseif is_mode("release") then
        add_defines("VM_RELEASE")
    end
  
    if is_plat("windows") then
      local win_defines = {
        "PF_WINDOWS",
        "WIN32_LEAN_AND_MEAN",
        "NOMINMAX"
      }

      add_defines(win_defines)
    
      add_syslinks("d3d11", "dxgi", "d3dcompiler")

    end

    if is_plat("linux") then 
        add_defines("PF_LINUX")
    end

    -- Output directories
    set_targetdir("$(projectdir)/bin/$(mode)")
    set_objectdir("$(projectdir)/obj/$(mode)/$(name)")
