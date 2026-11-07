#include "core/types/types.h"
#include "core/types/result.h"
#include "core/logger/log.h"


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
    auto a = vm::result<vm::u32, std::string>::failure("Notitu poiruchu");
    auto b = vm::result<vm::u32, std::string>::success(67);
   
    print_result(a);
    print_result(b);
}

