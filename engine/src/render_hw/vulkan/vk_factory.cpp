#include "vk_factory.h"
#include "core/logger/log.h"

VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE


vm::result<vm::scope<vm::rh::factory>, vm::error> vm::rh::factory::create_new() {
    auto res = rh::vuk::factory::internal_create_new();
    if (!res) {
        return failure<vm::error>(res.error());
    }
    return scope<vm::rh::factory>(*res);
}


NS(rh::vuk)

result <factory*, error> factory::internal_create_new() {
    VULKAN_HPP_DEFAULT_DISPATCHER.init(vkGetInstanceProcAddr);
    auto fact = new_scope<factory>();
    fact->setup_extensions_and_layers();
    if (!fact->extensions_supported() || !fact->layers_supported()) {
        return failure<error>("Extensions or layers not supported. Check log");
    }

    auto instance_res = fact->create_instance();
    if (instance_res != vk::Result::eSuccess) {
        auto msg = std::format("Failed to create instance: {}", vk::to_string(instance_res));
        return failure<error>(msg);
    }
    
    auto dbg_msgr_res = fact->setup_debug_messenger();
    if (dbg_msgr_res != vk::Result::eSuccess) {
        auto msg = std::format("Failed to setup debug messenger: {}", vk::to_string(dbg_msgr_res));
        return failure<error>(msg);
    }

    fact->_instance.submitDebugUtilsMessageEXT(
vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo,
   vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral,
   vk::DebugUtilsMessengerCallbackDataEXT {
            .pMessage = "vulkan factory initialization successful! (log from vulkan debug callback)"
        }
    );

    return fact.release();
}

vk::Result factory::create_instance() {
    vk::ApplicationInfo app_info {
        .sType = vk::StructureType::eApplicationInfo,
        .pApplicationName = "vanmam",
        .applicationVersion = vk::makeVersion(1, 0, 0),
        .pEngineName = "vanmam_rhw",
        .engineVersion = vk::makeVersion(1, 0, 0),
        .apiVersion = vk::ApiVersion14
    };

    vk::InstanceCreateInfo create_info {
        .sType = vk::StructureType::eInstanceCreateInfo,
        .pApplicationInfo = &app_info,
        .enabledLayerCount = static_cast<u32>(_layers.size()),
        .ppEnabledLayerNames = _layers.data(),
        .enabledExtensionCount = static_cast<u32>(_extensions.size()),
        .ppEnabledExtensionNames = _extensions.data()
    };

    auto [res, inst] = vk::createInstance(create_info);


    if (res != vk::Result::eSuccess) {
        return res;
    }

    _instance = std::move(inst);
    VULKAN_HPP_DEFAULT_DISPATCHER.init(_instance);
    return res;
}

void factory::setup_extensions_and_layers() {
    _extensions.push_back("VK_KHR_surface");
#ifdef PF_WINDOWS
    _extensions.push_back("VK_KHR_win32_surface");
#elif defined(PF_LINUX)
    #error "LINUX not supported. YET. POSSIBLY IN FUTURE. SIT TIGHT"
#endif

#ifdef VM_DEBUG
    _extensions.push_back("VK_EXT_debug_utils");
    _layers.push_back("VK_LAYER_KHRONOS_validation");
#endif

}

bool factory::extensions_supported() const {
    auto [res, required_extensions] = vk::enumerateInstanceExtensionProperties();

    if (res != vk::Result::eSuccess) {
        VM_LOG(VM_ERR, "Failed to retrieve extensions: {}", vk::to_string(res));
        return false;
    }

    for (const char* extension : _extensions) {
        bool found = std::ranges::any_of(required_extensions, [extension](const vk::ExtensionProperties& required_extension) {
            return std::strcmp(extension, required_extension.extensionName) == 0;
        });

        if (!found) {
            VM_LOG(VM_ERR, "Extension not supported: {}", extension);
            return false;
        }
    }
    return true;
}

bool factory::layers_supported() const {
    auto [res, required_layers] = vk::enumerateInstanceLayerProperties();

    if (res != vk::Result::eSuccess) {
        VM_LOG(VM_ERR, "Failed to retrieve layers: {}", vk::to_string(res));
        return false;
    }

    for (const char* layer : _layers) {
        bool found = std::ranges::any_of(required_layers, [layer](const vk::LayerProperties& required_layer) {
            return std::strcmp(layer, required_layer.layerName) == 0;
        });

        if (!found) {
            VM_LOG(VM_ERR, "Layer not supported: {}", layer); 
            return false;
        }
    }
    return true;
}

VKAPI_ATTR vk::Bool32 VKAPI_CALL factory::debug_callback(
    vk::DebugUtilsMessageSeverityFlagBitsEXT in_message_severity,
    [[maybe_unused]] vk::DebugUtilsMessageTypeFlagsEXT in_message_type,
    const vk::DebugUtilsMessengerCallbackDataEXT* in_callback_data,
    [[maybe_unused]] void* in_user_data
) {
    auto log_level = VM_INF;

    switch(in_message_severity) {
    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo:
        log_level = VM_INF;
        break;

    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning:
        log_level = VM_WRN;
        break;

    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eError:
        log_level = VM_ERR;
        break;

    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose:
        log_level = VM_FAT;
        break;
    }

    VM_LOG(log_level, "{}", in_callback_data->pMessage);
    return vk::False;
}

vk::Result factory::setup_debug_messenger() {
    vk::DebugUtilsMessengerCreateInfoEXT create_info {
        .messageSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo |
                           vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                           vk::DebugUtilsMessageSeverityFlagBitsEXT::eError |
                           vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose,
        .messageType = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                       vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
                       vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
        .pfnUserCallback = debug_callback,
        .pUserData = nullptr
    };

    auto [res, messenger] = _instance.createDebugUtilsMessengerEXT(create_info);
    _debug_messenger = std::move(messenger);
    return res;
}

factory::~factory() {
    if (_instance) {
        if (_debug_messenger) {
            _instance.destroyDebugUtilsMessengerEXT(_debug_messenger);
        }
        _instance.destroy();
    }
}



END_NS