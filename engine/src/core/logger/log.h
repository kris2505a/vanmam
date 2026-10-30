#pragma once
#include "core/core.h"
#include <core/types/types.h>

#include <format>

NS_VANMAM

enum class log_type {
    info = 0,
    debug,
    warn,
    error,
    fatal
};

#define VM_DBG vm::log_type::debug
#define VM_WRN vm::log_type::warn
#define VM_INF vm::log_type::info
#define VM_ERR vm::log_type::error
#define VM_FAT vm::log_type::fatal

#define VM_LOG(type, msg, ...) vm::core_log::format_and_log(PROJECT_NAME, type, msg, __VA_ARGS__)

class VANMAM_API core_log {
public:
    template<typename... Args>
    static void format_and_log(std::string_view project_name, log_type type, std::string_view str, Args&&... args) {
        auto msg = std::vformat(str, std::make_format_args(args...));
        log_message(project_name, type, msg);
    }
private:
    static std::string to_string(log_type type);
    static void log_message(std::string_view project_name, log_type type, std::string_view message);
};

END_NS
