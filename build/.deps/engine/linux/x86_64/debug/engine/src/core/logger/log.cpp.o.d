{
    files = {
        "engine/src/core/logger/log.cpp"
    },
    values = {
        "/usr/bin/clang++",
        {
            "-Qunused-arguments",
            "-m64",
            "-fPIC",
            "-g",
            "-O0",
            "-std=c++20",
            "-Iengine/src",
            "-Iengine/deps/glfw/include",
            "-Iengine/deps/glfw/src",
            "-DVM_SHARE_BUILD",
            "-DPROJECT_NAME=\"vanmam\"",
            "-DVM_DEBUG",
            "-DVM_PLATFORM_LINUX",
            "-Wall",
            "-Wextra"
        }
    },
    depfiles_format = "gcc",
    depfiles = "/home/krishna/projects/vanmam/obj/debug/engine/linux/x86_64/debug/engine/src/core/logger/__cpp_log.cpp.cpp:   engine/src/core/logger/log.cpp engine/src/core/logger/log.h   engine/src/core/core.h engine/src/core/types/types.h\
"
}