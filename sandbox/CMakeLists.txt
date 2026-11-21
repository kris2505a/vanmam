file(GLOB_RECURSE SANDBOX_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE SANDBOX_HEADERS CONFIGURE_DEPENDS "src/*.h")

add_executable(sandbox
    ${SANDBOX_SOURCES}
    ${SANDBOX_HEADERS}
)

target_include_directories(sandbox PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Links engine and automatically inherits engine's PUBLIC include directories (engine/src)
target_link_libraries(sandbox PRIVATE
    engine
)

target_compile_definitions(sandbox PRIVATE
    PROJECT_NAME="sandbox"
    $<$<PLATFORM_ID:Windows>:PF_WINDOWS>
    $<$<PLATFORM_ID:Linux>:PF_LINUX>
    UNICODE
    _UNICODE
)

set_target_properties(sandbox PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>"
)
