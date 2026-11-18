{
    files = {
        [[engine\src\core\logger\log.cpp]]
    },
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
    depfiles_format = "gcc",
    depfiles = "C:\\Users\\krishna\\projects\\Vanmam\\obj\\debug\\engine\\mingw\\x64\\debug\\engine\\src\\core\\logger\\__cpp_log.cpp.cpp:   engine/src/core/logger/log.cpp engine/src/core/logger/log.h   engine/src/core/core.h engine/src/core/types/types.h\
"
}