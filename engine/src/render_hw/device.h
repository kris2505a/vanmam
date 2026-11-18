#pragma once
#include "core/core.h"
#include <type_traits>
#include "core/types/types.h"
#include "core/types/error.h"

#include "render_hw/factory.h"

NS(rh) 

class VANMAM_API device {
public:
    virtual ~device() = default;

    template<typename T>
    requires std::is_base_of_v<device, T>
    T* as() {
        return dynamic_cast<T*>(this);
    }

    static result<scope<device>, error> create_new(factory* in_factory);
};

END_NS
