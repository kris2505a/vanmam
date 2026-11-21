#include "window.h"


NS(pf)


u32 window::get_width() const {
    return _create_info.width;
}

u32 window::get_height() const {
    return _create_info.height;
}

std::string_view window::get_title() const {
    return _create_info.title;
}

END_NS
