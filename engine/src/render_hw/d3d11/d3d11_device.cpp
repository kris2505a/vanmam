#include "d3d11_device.h"


NS(rh)


result <scope<device>, error> device::create_new() {
	auto res = d3d11_device::internal_create_new();
	if (!res.has_value()) {
		return result<scope<device>, error>::failure(res.get_error());
	}

	scope<device> dev(res.get_value());

	return result<scope<device>, error>::success(std::move(dev));
}

result<d3d11_device*, error> d3d11_device::internal_create_new() {

	auto* device = new d3d11_device();

	UINT flags = 0;
#ifdef VM_DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // VM_DEBUG

	HRESULT hr = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		flags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&device->_native_device,
		nullptr,
		&device->_native_context
	);

	if (FAILED(hr)) {
		return result<d3d11_device*, error>::failure({ hr });
	}
	
	return result<d3d11_device*, error>::success({ device });
}

ID3D11Device* d3d11_device::get_device_handle() const {
	return _native_device.Get();
}


END_NS

