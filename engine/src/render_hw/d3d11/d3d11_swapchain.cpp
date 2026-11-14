#include "d3d11_swapchain.h"
#include "d3d11_device.h"

NS(rh)

result <d3d11_swapchain*, error> d3d11_swapchain::internal_create_new(const swapchain_info& info, device& _device) {
	auto swapchain = new d3d11_swapchain();

	auto device = _device.as<d3d11_device>();

	if (!device) {
		return result<d3d11_swapchain*, error>::failure({ "Device is nullptr" });
	}

	com_ref<IDXGIDevice> dxgi_device;

}


END_NS