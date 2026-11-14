target("engine")
  local headers = {
    "input/input_codes.h",
    
    "logger/log.h",

    "types/error.h",
    "types/result.h",
    "types/types.h",

    "core.h"
  }

  local sources = {
    "logger/log.cpp"
  }

  
  add_files(sources)
  add_headerfiles(headers)
