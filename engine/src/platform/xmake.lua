target("engine")

  local sources = {
    "window.cpp",
    "cross_window/cross_window.cpp"
  }

  local headers = {
    "window.h",
    "cross_window/cross_window.h"
  }

  add_files(sources)
  add_headerfiles(headers)
