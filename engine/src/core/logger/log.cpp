#include "log.h"
#include <iostream>

NS_VANMAM

std::string core_log::to_string(log_type type) {
    switch (type) {
    case log_type::debug:
        return "deb";

    case log_type::info:
        return "inf";

    case log_type::error:
        return "err";

    case log_type::warn:
        return "wrn";

    case log_type::fatal:
        return "fat";
    }

    return "level unknown";
}

void core_log::log_message(std::string_view project_name, log_type type, std::string_view log_message) {
    std::cout << "$(" << core_log::to_string(type) << ") [" << project_name  << "] >> " << log_message << "\n";
}


END_NS
