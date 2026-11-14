#pragma once
#include "core/core.h"
#include "core/types/result.h"
#include "core/types/types.h"
#include "core/types/error.h"
#include "platform/native_handle.h"
#include "render_hw/device.h"

NS(rh)

struct swapchain_info {
	u32 width;
	u32 height;
	u32 buffer_count;
	const pf::native_handle* handle;
};


class VANMAM_API swapchain {
public:
    virtual ~swapchain() = default;

	virtual void present() = 0;

	static result<scope<swapchain>, error> create_new(const swapchain_info& info_, device& device_);

	template <typename T>
	requires std::is_base_of_v<swapchain, T>
	T* as() {
		return dynamic_cast<T*>(this);
	}

};

END_NS
