#pragma once
#include "core/core.h"
#include "types.h"
#include <string>
#include <source_location>
#include <ostream>
#include <format>


NS_VANMAM

class VANMAM_API error {
public:
    error(std::string_view error, const std::source_location& location = std::source_location::current()) 
        : _error(error), _file(location.file_name()), _func_called(location.function_name()), _line(location.line()) {}  
    ~error() = default;

    std::string_view get_error() const {
        return _error;
    }

    std::string_view get_file() const {
        return _file;
    }

    std::string_view get_func_name() const {
        return _func_called;
    }
    
    u32 get_line() const {
        return _line;
    }

private:
    std::string _error;
    std::string _file;
    std::string _func_called;
    u32 _line;
};

END_NS


template<>
struct std::formatter<vm::error> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(const vm::error& err, std::format_context& ctx) const {
        return std::format_to(
            ctx.out(),
            "{} | {} : {} : {}",
            err.get_error(),
            err.get_func_name(),
            err.get_file(),
            err.get_line()
        );
    }
};
