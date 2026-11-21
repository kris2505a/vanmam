#include "core/logger.h"
#include "platform/window.h"

#include "core/events.h"


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

    while (running) {
        window->pump_events();
    }
}

