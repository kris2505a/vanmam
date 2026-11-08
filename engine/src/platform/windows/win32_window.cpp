#include "win32_window.h"

NS(pf)

result<scope<window>, error> window::create_new(u32 width, u32 height, std::string_view title) {
	auto win = new_scope<win32_window>(width, height, title);
	
	win->setup_window_class();
	win->create_window();

	if (!win->get_handle()) {
		return result<scope<window>, error>::failure({ "Failed to create window" });
	}

	win->show_window();

	return result<scope<window>, error>::success(std::move(win));
}

win32_window::win32_window(u32 width, u32 height, std::string_view title)
	: window(width, height, title), _handle(nullptr), _instance(GetModuleHandleA(nullptr)), _window_class({}), _class_name("vanmam") {}

win32_window::~win32_window() {
	DestroyWindow(_handle);
}

void win32_window::poll_events() {
	MSG msg = { 0 };

	while (PeekMessageA(&msg, _handle, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

LRESULT CALLBACK win32_window::win_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void win32_window::setup_window_class() {
	_window_class = WNDCLASSEXA{
		.cbSize = sizeof(WNDCLASSEXA),
		.lpfnWndProc = win32_window::win_proc,
		.hInstance = _instance,
		.lpszClassName = _class_name.c_str(),
	};
	RegisterClassExA(&_window_class);
}

void win32_window::create_window() {
	_handle = CreateWindowExA(
		0,
		_class_name.c_str(),
		get_title().data(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		get_width(), get_height(),
		nullptr,
		nullptr,
		_instance,
		nullptr
	);
}

HWND win32_window::get_handle() const {
	return _handle;
}

void win32_window::show_window(){
	ShowWindow(_handle, SW_SHOWNA);
}

END_NS