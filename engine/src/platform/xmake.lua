target("engine")
  
  local headers = {
    "window.h",
    "native_handle.h"
  }

  local sources = {
    "window.cpp"
  }


  if is_plat("windows") then
    table.insert(headers, "windows/win32_window.h")
    table.insert(sources, "windows/win32_window.cpp")
  end

  add_files(sources)
  add_headerfiles(headers)
