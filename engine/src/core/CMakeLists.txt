target_sources(engine PRIVATE
    # Core
    "core.h"

    # Input
    "input/input_code.h"
    "input.h"

    # Logger
    "logger/log.h"
    "logger/log.cpp"
    "logger.h"

    # Types
    "types/error.h"
    "types/wrap_types.h"
    "types.h"

    # Event
    "event/event.h"
    "event/dispatcher.h"
    "events.h"
)
