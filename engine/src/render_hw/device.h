#pragma once
#include "core/core.h"

#include "core/types/types.h"
#include "core/types/result.h"
#include "core/types/error.h"

NS(rh) 

class VANMAM_API device {
public:
	static result <scope<device>, error> create_new();

	template <typename T>
	requires std::is_base_of_v<device, T>
	T* as() {
		return dynamic_cast<T*>(this);
	}

};

END_NS