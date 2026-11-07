#pragma once
#include "core/core.h"
#include "core/types/types.h"
#include <string>
#include "core/types/result.h"
#include "core/types/error.h"

NS(pf)

class VANMAM_API window {
public:
    window(u32 width, u32 height, std::string_view title);
    virtual ~window() = default;
    u32 get_width() const;
    u32 get_height() const;
    std::string_view get_title() const;

    //static result <scope<window>, error> create_new(u32 width, u32 height, std::string_view title);

    //virtual bool poll_events() = 0;


protected:
    u32 _width;
    u32 _heigh;
    std::string _title;
};


END_NS
