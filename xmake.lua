set_project("vanmam")
set_version("0.1.0")
set_languages("c++20")

-- Prevent xmake from auto-probing external toolchains/SDKs
add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {
    outputdir = "."
})

add_defines("_UNICODE", "UNICODE")

add_cxflags("/W4", "/wd4251", "/wd4273", { tools = "cl" })
includes("engine")
includes("sandbox")
