#pragma once
#include "render_hw/device.h"
#include <d3d11.h>

NS(rh)

class d3d11_device : public device {
public:
	d3d11_device() = default;
	~d3d11_device() = default;
	
	static result<d3d11_device*, error> internal_create_new();

	ID3D11Device* get_device_handle() const;

private:
	com_ref<ID3D11Device> _native_device;
	com_ref<ID3D11DeviceContext> _native_context;
};

END_NS