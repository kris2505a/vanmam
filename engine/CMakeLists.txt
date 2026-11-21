cmake_minimum_required(VERSION 3.20)

project(vanmam VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define the shared library target ("engine") with no initial sources
add_library(engine SHARED)

# Public include directories (equivalent to add_includedirs("src", {public = true}))
target_include_directories(engine PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Base compile definitions
target_compile_definitions(engine PRIVATE
    VM_SHARED_BUILD
    UNICODE
    _UNICODE
    PROJECT_NAME="vanmam"
    $<$<CONFIG:Debug>:VM_DEBUG>
    $<$<CONFIG:Release>:VM_RELEASE>
)

# Platform-specific defines and D3D11 linking
if(WIN32)
    target_compile_definitions(engine PRIVATE
        PF_WINDOWS
        WIN32_LEAN_AND_MEAN
        NOMINMAX
    )
    target_link_libraries(engine PRIVATE
        d3d11
        dxgi
	d3dcompiler
    )
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(engine PRIVATE
        PF_LINUX
    )
endif()

# Output directories (equivalent to $(projectdir)/bin/$(mode))
set_target_properties(engine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>"
)

# Subdirectories
add_subdirectory(src/core)
add_subdirectory(src/platform)
add_subdirectory(src/render_hw)
