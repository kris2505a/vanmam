#pragma once
#include "core/core.h"
#include "core/types/types.h"
#include <string>
#include "core/types/result.h"
#include "core/types/error.h"
#include "event/event.h"

#include <functional>

#include "native_handle.h"

NS(pf)

using CallbackFn = std::function<void(ev::event&)>;

struct window_create_info {
    u32 width;
    u32 height;
    std::string title;
    CallbackFn callback;
};

class VANMAM_API window {
public:
    window(const window_create_info& create_info);
    virtual ~window() = default;
    u32 get_width() const;
    u32 get_height() const;
    std::string_view get_title() const;

    static result <scope<window>, error> create_new(const window_create_info& create_info);

    virtual void pump_events() = 0;

    virtual const native_handle& get_native_handle() const = 0;


protected:
	u32 _width;
	u32 _heigh;
	std::string _title;
    CallbackFn _callback;

};


END_NS
