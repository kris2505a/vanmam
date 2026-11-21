file(GLOB_RECURSE ENGINE_RENDER_HEADERS CONFIGURE_DEPENDS "*.h")
file(GLOB_RECURSE ENGINE_RENDER_SOURCES CONFIGURE_DEPENDS "*.cpp")

target_sources(engine PRIVATE
    ${ENGINE_RENDER_HEADERS}
    ${ENGINE_RENDER_SOURCES}
)

if(WIN32)
    target_link_libraries(engine PRIVATE
        d3d11
        dxgi
    )
endif()
