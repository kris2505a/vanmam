#include "core/types/types.h"
#include "core/types/result.h"
#include "core/logger/log.h"
#include "platform/window.h"

#include "event/event.h"
#include "event/dispatcher.h"

#include "render_hw/device.h"


void print_result(vm::result<vm::u32, std::string>& res) {
    if (res.has_value()) {
        auto value = res.get_value();
        VM_LOG(VM_DBG, "{}", value);
    }
    else {
        auto error = res.get_error();
        VM_LOG(VM_ERR, "{}", error);
    }
}

bool running = true;

void handle_event(vm::ev::event& e) {
    vm::ev::dispatcher dp(e);

    dp.dispatch<vm::ev::key_press>([](const vm::ev::key_press& e) -> bool {
        VM_LOG(VM_DBG, "Key Pressed: {} | Repeat: {}", static_cast<vm::u16>(e.key), e.repeat);
        return true;
    });

    dp.dispatch<vm::ev::quit>([](const vm::ev::quit& e) -> bool {
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
        auto err = res.get_error();
        VM_LOG(VM_FAT, "{}", err);
    }
    
    auto window = res.get_value();

    auto dev_res = vm::rh::device::create_new();

    if (!dev_res.has_value()) {
        VM_LOG(VM_FAT, "{}", dev_res.get_error());
    }

    auto device = dev_res.get_value();



    while (running) {
        window->pump_events();
    }
}

