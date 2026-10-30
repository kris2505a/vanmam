#include "core/types/types.h"
#include "core/types/result.h"

#include "core/logger/log.h"

void output_result(const vm::Result<vm::u32, std::string>& result) {
    if (result.has_value()) {
        VM_LOG(VM_DBG, "The value is: {}", result.get_value());
        return;
    }
    VM_LOG(VM_ERR, "Error: {}", result.get_error());
}

int main() {
    vm::Result<vm::u32, std::string> a = vm::Result<vm::u32, std::string>::failure("Notitu poiruchu");
    vm::Result<vm::u32, std::string> b = vm::Result<vm::u32, std::string>::success(67);
    
    output_result(a);
    output_result(b);
}

