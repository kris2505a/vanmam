#include "window.h"


NS(pf)


window::window(const window_create_info& create_info)
    : _width(create_info.width), _heigh(create_info.height), _title(create_info.title), _callback(create_info.callback) {}


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
