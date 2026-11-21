target_sources(engine PRIVATE
    # Window
    "window.h"
    "window.cpp"
    "native_handle.h"
)

if(WIN32)
    target_sources(engine PRIVATE
        # Windows
        "windows/win32_window.h"
        "windows/win32_window.cpp"
    )
endif()
