{
    files = {
        "engine/deps/glfw/src/egl_context.c"
    },
    values = {
        "/usr/bin/clang",
        {
            "-Qunused-arguments",
            "-m64",
            "-fPIC",
            "-g",
            "-w",
            "-O0",
            "-std=c99",
            "-Iengine/deps/glfw/include",
            "-Iengine/deps/glfw/src",
            "-D_GLFW_BUILD_DLL",
            "-D_GLFW_X11",
            "-D_POSIX_C_SOURCE=199309L",
            "-D_DEFAULT_SOURCE",
            "-Wall",
            "-Wextra"
        }
    },
    depfiles_format = "gcc",
    depfiles = "build/.objs/GLFW/linux/x86_64/debug/engine/deps/glfw/src/__cpp_egl_context.c.c:   engine/deps/glfw/src/egl_context.c engine/deps/glfw/src/internal.h   engine/deps/glfw/src/../include/GLFW/glfw3.h   engine/deps/glfw/src/platform.h engine/deps/glfw/src/null_platform.h   engine/deps/glfw/src/x11_platform.h   engine/deps/glfw/src/null_joystick.h   engine/deps/glfw/src/linux_joystick.h   engine/deps/glfw/src/posix_thread.h engine/deps/glfw/src/posix_time.h   engine/deps/glfw/src/posix_poll.h   engine/deps/glfw/src/../include/GLFW/glfw3native.h\
"
}