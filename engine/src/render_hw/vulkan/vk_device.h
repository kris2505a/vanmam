#pragma once
#include "render_hw/device.h"
#include <vulkan/vulkan.hpp>

#include "vk_factory.h"

NS(rh::vlk)

class device : public vm::rh::device {
public:
    device() = default;
    ~device() override;
    static result <device*, error> internal_create_new(vlk::factory* in_factory);

private:
    bool pick_physical_device();
    vk::Result create_logical_device();
    bool device_valid(const vk::PhysicalDevice& device);
    void create_graphics_queue();

private:
    std::vector<const char*> _device_extensions;

    vk::PhysicalDevice _physical_device = nullptr;
    vk::Device _device = nullptr;
    u32 _graphics_queue_index = 0;
    vk::Queue _graphics_queue = nullptr;
    
    factory* _ref_factory = nullptr;

};

END_NS
