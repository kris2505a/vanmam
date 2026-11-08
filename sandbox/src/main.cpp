#include "core/types/types.h"
#include "core/types/result.h"
#include "core/logger/log.h"
#include "platform/window.h"


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

int main() {
    
    auto res = vm::pf::window::create_new(1280, 720, "Vanmam");
    if (!res.has_value()) {
        auto err = res.get_error();
        VM_LOG(VM_FAT, "{}", err);
    }

    auto window = res.get_value();

    while (true) {
        window->poll_events();
        VM_LOG(VM_DBG, "running...");
    }
}

