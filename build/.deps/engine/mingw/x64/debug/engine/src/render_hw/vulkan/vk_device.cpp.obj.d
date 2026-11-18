{
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
    files = {
        [[engine\src\render_hw\vulkan\vk_device.cpp]]
    },
    depfiles = "C:\\Users\\krishna\\projects\\Vanmam\\obj\\debug\\engine\\mingw\\x64\\debug\\engine\\src\\render_hw\\vulkan\\__cpp_vk_device.cpp.cpp:   engine/src/render_hw/vulkan/vk_device.cpp   engine/src/render_hw/vulkan/vk_device.h engine/src/render_hw/device.h   engine/src/core/core.h engine/src/core/types/types.h   engine/src/core/types/error.h engine/src/render_hw/factory.h   C:/VulkanSDK/1.4.363.1/Include/vulkan/vulkan.hpp   C:/VulkanSDK/1.4.363.1/Include/vulkan/vulkan.h   C:/VulkanSDK/1.4.363.1/Include/vulkan/vk_platform.h   C:/VulkanSDK/1.4.363.1/Include/vulkan/vulkan_core.h   C:/VulkanSDK/1.4.363.1/Include/vk_video/vulkan_video_codec_h264std.h   C:/VulkanSDK/1.4.363.1/Include/vk_video/vulkan_video_codecs_common.h   C:/VulkanSDK/1.4.363.1/Include/vk_video/vulkan_video_codec_h264std_encode.h   C:/VulkanSDK/1.4.363.1/Include/vk_video/vulkan_video_codec_h265std.h   C:/VulkanSDK/1.4.363.1/Include/vk_video/vulkan_video_codec_h265std_encode.h   C:/VulkanSDK/1.4.363.1/Include/vk_video/vulkan_video_codec_h264std_decode.h   C:/VulkanSDK/1.4.363.1/Include/vk_video/vulkan_video_codec_h265std_decode.h   C:/VulkanSDK/1.4.363.1/Include/vk_video/vulkan_video_codec_av1std.h   C:/VulkanSDK/1.4.363.1/Include/vk_video/vulkan_video_codec_av1std_decode.h   C:/VulkanSDK/1.4.363.1/Include/vk_video/vulkan_video_codec_av1std_encode.h   C:/VulkanSDK/1.4.363.1/Include/vk_video/vulkan_video_codec_vp9std.h   C:/VulkanSDK/1.4.363.1/Include/vk_video/vulkan_video_codec_vp9std_decode.h   C:/VulkanSDK/1.4.363.1/Include/vulkan/vulkan_hpp_macros.hpp   C:/VulkanSDK/1.4.363.1/Include/vulkan/vulkan_enums.hpp   C:/VulkanSDK/1.4.363.1/Include/vulkan/vulkan_to_string.hpp   C:/VulkanSDK/1.4.363.1/Include/vulkan/vulkan_handles.hpp   C:/VulkanSDK/1.4.363.1/Include/vulkan/vulkan_structs.hpp   C:/VulkanSDK/1.4.363.1/Include/vulkan/vulkan_funcs.hpp   engine/src/render_hw/vulkan/vk_factory.h engine/src/core/logger/log.h\
"
}