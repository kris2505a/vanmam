#pragma once
#include "platform/window.h"
#include <GLFW/glfw3.h>
#include "core/types/error.h"

NS(pf)

class cross_window : public window {
public:
    cross_window(u32 width, u32 height, std::string_view title);
    ~cross_window() override;

    static result<cross_window*, error> create_new(u32 width, u32 height, std::string_view title);
    
    bool poll_events() override;

private:
    GLFWwindow* _native_window;
    bool _context_initialized;
};


END_NS
