set_project("vanmam")
    set_version("0.1.0")
    set_languages("c++20")
    set_plat("windows")


    add_rules("mode.debug", "mode.release")
    add_rules("plugin.compile_commands.autoupdate", {
        outputdir = "."
    })

    add_cxflags("/utf-8", "/permissive-", {
        tools = "cl"
    })

    includes("engine")
    includes("testbed")