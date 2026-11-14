#pragma once
#include "platform/window.h"

#include <Windows.h>
#include "core/input/input_code.h"

NS(pf)

class win32_window : public window {
public:
	win32_window(const window_create_info& create_info);
	~win32_window();
	void pump_events() override;

	void setup_window_class();
	void create_window();
	void show_window();

	static key_code to_key_code(WPARAM vk, LPARAM data);
	const native_handle* get_native_handle() const override;
    HWND get_hwnd() const;


private:
	static LRESULT CALLBACK win_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);


private:
	windows_native_handle _native_handle;
	WNDCLASSEXW	_window_class;
	std::wstring _class_name;

};

END_NS
