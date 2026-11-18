#include "vk_device.h"
#include "core/logger/log.h"

vm::result<vm::scope<vm::rh::device>, vm::error> vm::rh::device::create_new(vm::rh::factory* in_factory) {
    if (!in_factory) {
        return failure<vm::error>("Factory is nullptr!");
    }
    auto res = vm::rh::vlk::device::internal_create_new(in_factory->as<vm::rh::vlk::factory>());
    if (!res.has_value()) {
        return failure<error>(res.error());
    }

    return scope<device> (*res);
}

NS(rh::vlk)

result <device*, error> device::internal_create_new(vlk::factory* in_factory) {
    if (!in_factory) {
        return failure<error>("factory is nullptr");
    }

    
    scope<device> dev = new_scope<device>();
    dev->_ref_factory = in_factory;
    dev->_device_extensions = { vk::KHRSwapchainExtensionName };
    if (!dev->pick_physical_device()) {
        return failure<error>("failed to retrieve physical device!");
    }

    auto res = dev->create_logical_device();
    if (res != vk::Result::eSuccess) {
        auto msg = std::format("Failed to create logical device: {}", vk::to_string(res));
        return failure<error>(msg);
    }

    dev->create_graphics_queue();
    return dev.release();
}

bool device::pick_physical_device() {
    auto& ref_instance = _ref_factory->instance();
    
    auto [res, phy_devices] = ref_instance.enumeratePhysicalDevices();
    
    if (res != vk::Result::eSuccess) {
        VM_LOG(VM_FAT, "No GPUs found!");
        return false;
    }

    const auto device_iter = std::find_if(phy_devices.begin(), phy_devices.end(), [&](const auto& pd) {
        return device_valid(pd);    
    });

    if (device_iter == phy_devices.end()) {
        VM_LOG(VM_FAT, "Supported GPU not found!");
        return false;    
    }

    _physical_device = *device_iter;
    return true; 
}

bool device::device_valid(const vk::PhysicalDevice& pd) {
    bool vk_1_3 = pd.getProperties().apiVersion >= vk::ApiVersion13;

    auto queue_families = pd.getQueueFamilyProperties();
    bool support_graphics = std::ranges::any_of(queue_families, [](const vk::QueueFamilyProperties& qfp) {
        return !!(qfp.queueFlags & vk::QueueFlagBits::eGraphics);
    });

    bool support_extensions = true;
    
    auto required_extensions = pd.enumerateDeviceExtensionProperties();
    
    for (const char* ext : _device_extensions) {
        bool supported = std::any_of(required_extensions->begin(), required_extensions->end(), [ext](const auto& req_ex) {
            return std::strcmp(ext, req_ex.extensionName) == 0;
        });

        if (!supported) {
            support_extensions = false;
            VM_LOG(VM_ERR, "Extension not supported: {}", ext);
            break;
        }
    }
    
    auto features = pd.getFeatures2<
        vk::PhysicalDeviceFeatures2,
        vk::PhysicalDeviceVulkan11Features,
        vk::PhysicalDeviceVulkan13Features,
        vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT
    >();

    bool support_features = features.get<vk::PhysicalDeviceVulkan11Features>().shaderDrawParameters &&
    features.get<vk::PhysicalDeviceVulkan13Features>().dynamicRendering     &&
    features.get<vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>().extendedDynamicState;
    
    VM_LOG(VM_INF, "Vulkan 1.3: {}", vk_1_3);
    VM_LOG(VM_INF, "Graphics queue: {}", support_graphics);
    VM_LOG(VM_INF, "Required extensions: {}", support_extensions);
    VM_LOG(VM_INF, "Required features: {}", support_features);

    return vk_1_3 && support_graphics && support_extensions && support_features;
}

vk::Result device::create_logical_device() {
    auto queue_family_properties = _physical_device.getQueueFamilyProperties();
    auto queue_family_property = std::find_if(queue_family_properties.begin(), queue_family_properties.end(), [] (const auto& qfp) {
        return (qfp.queueFlags & vk::QueueFlagBits::eGraphics) != static_cast<vk::QueueFlags>(0);
    });

    _graphics_queue_index = static_cast<u32>(std::distance(queue_family_properties.begin(), queue_family_property));


    float queue_priority = 0.5f;

    vk::DeviceQueueCreateInfo queue_info {
        .queueFamilyIndex = _graphics_queue_index,
        .queueCount = 1,
        .pQueuePriorities = &queue_priority
    };


    // Create a chain of feature structures
    vk::StructureChain<vk::PhysicalDeviceFeatures2,
                   vk::PhysicalDeviceVulkan11Features,
                   vk::PhysicalDeviceVulkan13Features,
                   vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>
    feature_chain = {
        {},                                    // vk::PhysicalDeviceFeatures2 (empty for now)
        {.shaderDrawParameters = true},        // Enable shader draw parameters from Vulkan 1.1
        {.dynamicRendering = true},            // Enable dynamic rendering from Vulkan 1.3
        {.extendedDynamicState = true}         // Enable extended dynamic state from the extension
    };

    vk::DeviceCreateInfo device_info {
        .pNext = &feature_chain.get<vk::PhysicalDeviceFeatures2>(),
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &queue_info,
        .enabledExtensionCount = static_cast<u32>(_device_extensions.size()),
        .ppEnabledExtensionNames = _device_extensions.data()
    };

    auto res = _physical_device.createDevice(&device_info, nullptr, &_device);
    return res;
}

void device::create_graphics_queue() {
    _graphics_queue = _device.getQueue(_graphics_queue_index, 0);
}

device::~device() {
    if (_device) {
        _device.destroy();
    }
}

END_NS
