#pragma once
#include "render_hw/factory.h"

#include <vulkan/vulkan.hpp>

NS(rh::vlk) 

class factory : public rh::factory {
public:
    factory() = default;
    ~factory();
    const std::vector<const char*> get_required_extensions() const;
    static result <factory*, error> internal_create_new();

    const vk::Instance& instance() const;

private:
    vk::Result create_instance();
    vk::Result setup_debug_messenger();
    void setup_extensions_and_layers();
    bool extensions_supported() const;
    bool layers_supported() const;

    static VKAPI_ATTR vk::Bool32 VKAPI_CALL debug_callback(
        vk::DebugUtilsMessageSeverityFlagBitsEXT in_message_severity,
        vk::DebugUtilsMessageTypeFlagsEXT in_message_type,
        const vk::DebugUtilsMessengerCallbackDataEXT* in_callback_data,
        void* in_user_data
    );

private:
    vk::Instance _instance = nullptr;
    vk::DebugUtilsMessengerEXT _debug_messenger = nullptr;
    std::vector<const char*> _extensions;
    std::vector<const char*> _layers;
};

END_NS
