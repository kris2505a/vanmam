#pragma once
#include "render_hw/swapchain.h"
#include <dxgi.h>
#include <dxgi1_2.h>
#include <d3d11.h>


NS(rh)

class d3d11_swapchain : public swapchain {
public:
	d3d11_swapchain() = default;
	~d3d11_swapchain() = default;

	static result <d3d11_swapchain*, error> internal_create_new(const swapchain_info& info, device& _device);
	void present() override;

private:
	HRESULT create_factory(ID3D11Device* device);
	HRESULT create_swapchain(ID3D11Device* device);

private:
	com_ref<IDXGISwapChain1> _native_swapchain;
	com_ref<IDXGIFactory2> _native_factory;
	swapchain_info _info;
};

END_NS	