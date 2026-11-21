#pragma once
#include "core/core.h"


NS_VANMAM

enum class status {
    success,
    failed_to_create_win32_window,
};


template <typename t_val>
struct result {
    status status_value;
    t_val value;
};


END_NS