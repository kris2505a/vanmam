{
    depfiles_format = "gcc",
    files = {
        "engine/src/platform/cross_window/cross_window.cpp"
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
    depfiles = "/home/krishna/projects/vanmam/obj/debug/engine/linux/x86_64/debug/engine/src/platform/cross_window/__cpp_cross_window.cpp.cpp:   engine/src/platform/cross_window/cross_window.cpp   engine/src/platform/cross_window/cross_window.h   engine/src/platform/window.h engine/src/core/core.h   engine/src/core/types/types.h engine/src/core/types/result.h   engine/src/core/types/error.h engine/deps/glfw/include/GLFW/glfw3.h\
"
}