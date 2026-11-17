includes("src/core")
includes("src/platform")
includes("src/event")
includes("src/render_hw")

local vulkan_sdk = os.getenv("VULKAN_SDK")

target("engine")
    set_kind("shared")

    add_includedirs("src", {public = true})

    local defines = {
        "VM_SHARED_BUILD",
        "UNICODE", "_UNICODE",
        "PROJECT_NAME=\"vanmam\""
    }


    if is_mode("debug") then
        table.insert(defines, "VM_DEBUG")
    elseif is_mode("release") then
        table.insert(defines, "VM_RELEASE")
    end
  
    if is_plat("windows") then
      table.insert(defines, "PF_WINDOWS")
      table.insert(defines, "WIN32_LEAN_AND_MEAN")
      table.insert(defines, "NOMINMAX")

    elseif is_plat("linux") then 
      table.insert(defines, "PF_LINUX")
    end

    add_defines(defines)

    add_includedirs(path.join(vulkan_sdk, "Include"))
    add_linkdirs(path.join(vulkan_sdk, "Lib"))
    add_links("vulkan-1")

    -- Output directories
    set_targetdir("$(projectdir)/bin/$(mode)")
    set_objectdir("$(projectdir)/obj/$(mode)/$(name)")
