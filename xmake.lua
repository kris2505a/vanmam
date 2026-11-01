set_project("vanmam")
set_version("0.1.0")
set_languages("c++20")

-- Lock down toolchain discovery
set_toolchains("clang")

-- Prevent xmake from auto-probing external toolchains/SDKs
add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {
    outputdir = "."
})

add_cxflags("-Wall", "-Wextra")    
includes("engine")
includes("sandbox")
