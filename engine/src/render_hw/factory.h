#pragma once
#include "core/core.h"
#include "core/types/types.h"
#include "core/types/error.h"

NS(rh) 

class VANMAM_API factory {
public:
    virtual ~factory() = default;
    static std::expected<scope<factory>, error> create_new();

};

END_NS