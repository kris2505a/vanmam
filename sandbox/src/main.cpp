#include "core/logger/log.h"
#include "platform/window.h"

#include "event/event.h"
#include "event/dispatcher.h"

#include "render_hw/factory.h"
#include "render_hw/device.h"


bool running = true;

void handle_event(vm::ev::event& e) {
    vm::ev::dispatcher dp(e);

    dp.dispatch<vm::ev::quit>([](const vm::ev::quit& e) -> bool {
        VM_LOG(VM_INF, "exit code: {}", e.exit_code);
        running = false;
        return true;
    });

}

int main() {
    
    auto info = vm::pf::window_create_info{
        .width = 1280,
        .height = 720,
        .title = "vanmam",
        .callback = std::bind(handle_event, std::placeholders::_1)
    };

    auto res = vm::pf::window::create_new(info);
    if (!res.has_value()) {
        auto err = res.error();
        VM_LOG(VM_FAT, "{}", err);
        return -1;
    }
    
    auto window = std::move(*res);

    auto fact_res = vm::rh::factory::create_new();
    if (!fact_res) {
        auto err = fact_res.error();
        VM_LOG(VM_FAT, "Failed to create factory: {}", err);
        return -1;
    }

    auto factory = std::move(*fact_res);

    auto dev_res = vm::rh::device::create_new(factory.get());

    if (!dev_res) {
        auto err = dev_res.error();
        VM_LOG(VM_FAT, "Failed to create device: {}", err);
        return -1;
    }

    auto device = std::move(*dev_res);

    while (running) {
        window->pump_events();
    }
}

