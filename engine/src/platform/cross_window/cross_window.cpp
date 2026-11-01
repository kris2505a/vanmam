#include "cross_window.h"

NS(pf)

cross_window::cross_window(u32 width, u32 height, std::string_view title)
: window(width, height, title) {}

result<cross_window*, error> cross_window::create_new(u32 width, u32 height, std::string_view title) {
    cross_window* window = new cross_window(width, height, title);
    if (!glfwInit()) {
        return result<cross_window*, error>::failure({ "Failed to init glfw!" });
    }

    window->_native_window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    if (!window->_native_window) {
        return result<cross_window*, error>::failure({ "Failed to create window!" });
    }
    return result<cross_window*, error>::success(window);
}

cross_window::~cross_window() {
    if (_native_window) {
        glfwDestroyWindow(_native_window);
    }

    glfwTerminate();
}

bool cross_window::poll_events() {
    glfwPollEvents();
    return true;
}

END_NS
