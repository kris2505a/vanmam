#include "window.h"

NS(pf)


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
