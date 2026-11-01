{
    files = {
        "sandbox/src/main.cpp"
    },
    values = {
        "/usr/bin/clang++",
        {
            "-Qunused-arguments",
            "-m64",
            "-g",
            "-O0",
            "-std=c++20",
            "-Isandbox/src",
            "-Iengine/src",
            "-Iengine/deps/glfw/include",
            "-Iengine/deps/glfw/src",
            "-DPROJECT_NAME=\"testbed\"",
            "-DVM_PLATFORM_LINUX",
            "-Wall",
            "-Wextra"
        }
    },
    depfiles_format = "gcc",
    depfiles = "/home/krishna/projects/vanmam/obj/debug/sandbox/linux/x86_64/debug/sandbox/src/__cpp_main.cpp.cpp:   sandbox/src/main.cpp engine/src/core/types/types.h   engine/src/core/core.h engine/src/core/types/result.h   engine/src/core/logger/log.h engine/src/platform/window.h   engine/src/core/types/error.h\
"
}