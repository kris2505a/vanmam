target("engine")
    set_kind("shared")

    add_files("src/Engine.cpp")
    add_headerfiles("src/Engine.h")

    add_includedirs("src", {
        public = true
    })

    add_syslinks("d3d12", "dxgi", "dxguid", {
        public = true
    })

    local defines = {
        "VM_SHARE_BUILD",
        "WIN32_LEAN_AND_MEAN",
        "NOMINMAX",
        "PROJECT_NAME=\"vanmam\""
    }

    if is_mode("debug") then
        table.insert(defines, "VM_DEBUG")
    elseif is_mode("release") then
        table.insert(defines, "VM_RELEASE")
    end

    add_defines(defines)



    set_targetdir("$(projectdir)/bin/$(mode)")
    set_objectdir("$(projectdir)/obj/$(mode)/$(name)")
    
    includes("src/core")
