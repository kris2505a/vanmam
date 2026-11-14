#include "d3d11_swapchain.h"
#include "d3d11_device.h"

NS(rh)

result <scope<swapchain>, error> swapchain::create_new(const swapchain_info& in_info, device& in_device) {
	auto res = d3d11_swapchain::internal_create_new(in_info, in_device);
	if (!res.has_value()) {
		return result<scope<swapchain>, error>::failure(res.get_error());
	}

	scope<swapchain> spch(res.get_value());
	return result<scope<swapchain>, error>::success(std::move(spch));
}

result <d3d11_swapchain*, error> d3d11_swapchain::internal_create_new(const swapchain_info& in_info, device& in_device) {
	auto swapchain = new_scope<d3d11_swapchain>();
	swapchain->_info = in_info;	

	auto device = in_device.as<d3d11_device>();

	if (!device) {
		return result<d3d11_swapchain*, error>::failure({ "Device is nullptr" });
	}

	auto hr = swapchain->create_factory(device->get_device_handle());

	if (FAILED(hr)) {
		return result <d3d11_swapchain*, error>::failure({ hr });
	}

	hr = swapchain->create_swapchain(device->get_device_handle());

	if (FAILED(hr)) {
		return result <d3d11_swapchain*, error>::failure({ hr });
	}
	return result <d3d11_swapchain*, error>::success(swapchain.release());
}

HRESULT d3d11_swapchain::create_factory(ID3D11Device* in_device) {
	HRESULT hr;
	com_ref<IDXGIDevice> dxgi_device;
	hr = in_device->QueryInterface(IID_PPV_ARGS(&dxgi_device));
	if (FAILED(hr)) {
		return hr;
	}

	com_ref<IDXGIAdapter> dxgi_adapter;
	hr = dxgi_device->GetAdapter(&dxgi_adapter);
	
	if (FAILED(hr)) {
		return hr;
	}

	hr = dxgi_adapter->GetParent(IID_PPV_ARGS(&_native_factory));
	return hr;
}

HRESULT d3d11_swapchain::create_swapchain(ID3D11Device* in_device) {

	DXGI_SWAP_CHAIN_DESC1 sd {
		.Width = _info.width,
		.Height = _info.height,
		.Format = DXGI_FORMAT_R8G8B8A8_UNORM,
		.Stereo = FALSE,
		.SampleDesc = {
			.Count = 1,
			.Quality = 0
		},
		.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
		.BufferCount = _info.buffer_count,
		.Scaling = DXGI_SCALING_STRETCH,
		.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD,
		.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED,
		.Flags = 0
	};

	auto window_handle = static_cast<const pf::windows_native_handle*>(_info.handle);

	VM_ASSERT(window_handle);

	return _native_factory->CreateSwapChainForHwnd(
		in_device,
		window_handle->handle,
		&sd,
		nullptr,
		nullptr,
		&_native_swapchain
	);
}

void d3d11_swapchain::present() {
	_native_swapchain->Present(1, 0);
}


END_NS
