#pragma once
#include "render_hw/swapchain.h"
#include <dxgi.h>
#include <dxgi1_2.h>


NS(rh)

class d3d11_swapchain : public swapchain {
public:
	d3d11_swapchain() = default;
	~d3d11_swapchain() = default;

	static result <d3d11_swapchain*, error> internal_create_new(const swapchain_info& info, device& _device);

private:
	com_ref<IDXGISwapChain> _native_swapchain;
};

END_NS	