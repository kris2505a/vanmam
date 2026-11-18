{
    values = {
        [[C:\mingw64\bin\clang++]],
        {
            "-Qunused-arguments",
            "-m64",
            "-g",
            "-O0",
            "-std=c++23",
            [[-Isandbox\src]],
            [[-Iengine\src]],
            "-D_UNICODE",
            "-DUNICODE",
            "-DPROJECT_NAME=\"testbed\"",
            "-DPF_WINDOWS",
            "-Wall",
            "-Wextra",
            "-Wpedantic"
        }
    },
    files = {
        [[sandbox\src\main.cpp]]
    },
    depfiles_format = "gcc",
    depfiles = "C:\\Users\\krishna\\projects\\Vanmam\\obj\\debug\\sandbox\\mingw\\x64\\debug\\sandbox\\src\\__cpp_main.cpp.cpp:   sandbox/src/main.cpp engine/src/core/logger/log.h   engine/src/core/core.h engine/src/core/types/types.h   engine/src/platform/window.h engine/src/core/types/error.h   engine/src/event/event.h engine/src/core/input/input_code.h   engine/src/platform/native_handle.h engine/src/event/dispatcher.h   engine/src/render_hw/factory.h engine/src/render_hw/device.h\
"
}