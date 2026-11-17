set_project("vanmam")
set_version("0.1.0")
set_languages("cxx23")
set_toolchains("clang")

add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {
    outputdir = "."
})

add_defines("_UNICODE", "UNICODE")

add_cxflags("-Wall", "-Wextra", "-Wpedantic", { tools = "clang" })

includes("engine")
includes("sandbox")