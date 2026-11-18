{
    files = {
        [[engine\src\platform\windows\win32_window.cpp]]
    },
    depfiles_format = "gcc",
    values = {
        [[C:\mingw64\bin\clang++]],
        {
            "-Qunused-arguments",
            "-m64",
            "-g",
            "-O0",
            "-std=c++23",
            [[-Iengine\src]],
            [[-IC:\VulkanSDK\1.4.363.1\Include]],
            "-D_UNICODE",
            "-DUNICODE",
            "-DVULKAN_HPP_NO_STRUCT_CONSTRUCTORS",
            "-DVULKAN_HPP_NO_EXCEPTIONS",
            "-DVULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1",
            "-DVM_SHARED_BUILD",
            "-DPROJECT_NAME=\"vanmam\"",
            "-DVM_DEBUG",
            "-DPF_WINDOWS",
            "-DWIN32_LEAN_AND_MEAN",
            "-DNOMINMAX",
            "-Wall",
            "-Wextra",
            "-Wpedantic"
        }
    },
    depfiles = "C:\\Users\\krishna\\projects\\Vanmam\\obj\\debug\\engine\\mingw\\x64\\debug\\engine\\src\\platform\\windows\\__cpp_win32_window.cpp.cpp:   engine/src/platform/windows/win32_window.cpp   engine/src/platform/windows/win32_window.h   engine/src/platform/window.h engine/src/core/core.h   engine/src/core/types/types.h engine/src/core/types/error.h   engine/src/event/event.h engine/src/core/input/input_code.h   engine/src/platform/native_handle.h engine/src/core/logger/log.h\
"
}