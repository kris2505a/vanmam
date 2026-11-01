#include "core/types/types.h"
#include "core/types/result.h"

#include "core/logger/log.h"

#include "platform/window.h"

#include <thread>

#include <iostream>

int main() {
    auto a = vm::result<vm::u32, std::string>::failure("Notitu poiruchu");
    auto b = vm::result<vm::u32, std::string>::success(67);
    
    auto res = vm::pf::window::create_new(1280, 720, "olegam");
    if (!res.has_value()) {
        auto err = res.get_error();
        VM_LOG(VM_FAT, "{}", err);
    }

    auto window = res.get_value();
    
    std::atomic<bool> running = true;
    
    std::jthread listener([&]{
        char c;
        std::cin >> c;
        if (c == 'Q' || c == 'q') {
            running = false;
        }
    });

    while (running) {
        window->poll_events();
    }

}

