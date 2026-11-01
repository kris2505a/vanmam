target("engine")

    local sources = {
        "logger/log.cpp"
    }

    local headers = {
        "types/types.h",
        "logger/log.h",
        "types/error.h",
        "types/result.h"
    }

    add_files(sources)
    add_headerfiles(headers)
