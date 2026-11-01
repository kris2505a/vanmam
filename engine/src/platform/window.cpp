#include "window.h"
#include "cross_window/cross_window.h"

NS(pf)

result<scope<window>, error> window::create_new(u32 width, u32 height, std::string_view title) {
    auto res = cross_window::create_new(width, height, title);
    if (!res.has_value()) {
        return result<scope<window>, error>::failure(res.get_error());
    }
    cross_window* raw = res.get_value();
    return result <scope<window>, error>::success(scope<window>(raw));
}

window::window(u32 width, u32 height, std::string_view title)
    : _width(width), _heigh(height), _title(title) {}


u32 window::get_width() const {
    return _width;
}

u32 window::get_height() const {
    return _heigh;
}

std::string_view window::get_title() const {
    return _title;
}

END_NS
