#include "win32_window.h"
#include "core/logger/log.h"


#include <windowsx.h>

NS(pf)

result<scope<window>, error> window::create_new(const window_create_info& create_info) {
	auto win = new_scope<win32_window>(create_info);
	
	win->setup_window_class();
	win->create_window();

	if (!win->get_hwnd()) {
		return result<scope<window>, error>::failure({ "Failed to create window" });
	}

	win->show_window();

	return result<scope<window>, error>::success(std::move(win));
}

win32_window::win32_window(const window_create_info& create_info)
	: window(create_info), _window_class({}), _class_name(L"vanmam") {}

win32_window::~win32_window() {
	DestroyWindow(_native_handle.handle);
}

void win32_window::pump_events() {
	MSG msg = { 0 };
	while (PeekMessageW(&msg, _native_handle.handle, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

LRESULT CALLBACK win32_window::win_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

	win32_window* win = reinterpret_cast<win32_window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));

	if (!win) {
		VM_LOG(VM_ERR, "Failed to retrieve long ptr to window object. Defaulting to DefWindowProc");
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	auto& callback = win->_callback;

	switch (msg) {

	case WM_DESTROY: {
		ev::quit e{};
		callback(e);
		break;
	}

	case WM_QUIT:
		PostQuitMessage(0);
		break;

	case WM_SYSKEYDOWN:
	case WM_KEYDOWN: {
		bool repeat = (lparam & 0x40000000) != 0;
		ev::key_press e(to_key_code(wparam, lparam), repeat);
		callback(e);
		break;
	}

	case WM_SYSKEYUP:
	case WM_KEYUP: {
		ev::key_release e(to_key_code(wparam, lparam));
		callback(e);
		break;
	}

	case WM_LBUTTONDOWN: {
		ev::button_press e(button_code::left_mouse);
		callback(e);
		break;
	}

	case WM_RBUTTONDOWN: {
		ev::button_press e(button_code::right_mouse);
		callback(e);
		break;
	}

	case WM_MBUTTONDOWN: {
		ev::button_press e(button_code::middle_mouse);
		callback(e);
		break;
	}

	case WM_LBUTTONUP: {
		ev::button_release e(button_code::left_mouse);
		callback(e);
		break;
	}

	case WM_RBUTTONUP: {
		ev::button_release e(button_code::right_mouse);
		callback(e);
		break;
	}

	case WM_MBUTTONUP: {
		ev::button_release e(button_code::middle_mouse);
		callback(e);
		break;
	}

	case WM_MOUSEMOVE: {
		i32 x = GET_X_LPARAM(lparam);
		i32 y = GET_Y_LPARAM(lparam);

		ev::mouse_move e(static_cast<f32>(x), static_cast<f32>(y));
		callback(e);
		break;
	}

	case WM_MOUSEWHEEL: {
		const i16 delta = GET_WHEEL_DELTA_WPARAM(wparam);

		ev::mouse_scroll e(
			0.0f,
			static_cast<f32>(delta) / WHEEL_DELTA
		);

		callback(e);
		break;
	}

	case WM_MOUSEHWHEEL: {
		const i16 delta = GET_WHEEL_DELTA_WPARAM(wparam);

		ev::mouse_scroll e(
			static_cast<f32>(delta) / WHEEL_DELTA,
			0.0f
		);

		callback(e);
		break;
	}

	}
	return DefWindowProcA(hwnd, msg, wparam, lparam);
}

void win32_window::setup_window_class() {
	_window_class = WNDCLASSEXW{
		.cbSize = sizeof(WNDCLASSEXW),
		.lpfnWndProc = win32_window::win_proc,
		.hInstance = _native_handle.instance,
		.lpszClassName = _class_name.c_str(),
	};
	RegisterClassExW(&_window_class);
}

void win32_window::create_window() {
	std::wstring title = to_wide(get_title());
	_native_handle.handle = CreateWindowExW(
		0,
		_class_name.c_str(),
		title.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		get_width(), get_height(),
		nullptr,
		nullptr,
		_native_handle.instance,
		nullptr
	);
	SetWindowLongPtrW(_native_handle.handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
}

void win32_window::show_window(){
	ShowWindow(_native_handle.handle, SW_SHOW);
}

key_code win32_window::to_key_code(WPARAM vk, LPARAM data) {

	
	const u32 scan_code = (data >> 16) & 0xFF;
	const bool extended = (data & (1LL << 24)) != 0;

	if (vk == VK_SHIFT) {
		vk = MapVirtualKeyW(scan_code, MAPVK_VSC_TO_VK_EX);
	}

	else if (vk == VK_CONTROL) {
		vk = extended ? VK_RCONTROL : VK_LCONTROL;
	}

	else if (vk == VK_MENU) {
		vk = extended ? VK_RMENU : VK_LMENU;
	}


	if (vk >= 'A' && vk <= 'Z') {
		return static_cast<key_code>(static_cast<u8>(key_code::a) + (vk - 'A'));
	}

	else if (vk >= '0' && vk <= '9') {
		return static_cast<key_code>(static_cast<u8>(key_code::n0) + (vk - '0'));
	}

	else if (vk >= VK_NUMPAD0 && vk <= VK_NUMPAD9) {
		return static_cast<key_code>(static_cast<u8>(key_code::np0) + (vk - VK_NUMPAD0));
	}
	
	else {
		switch (vk) {
		case VK_LCONTROL:
			return key_code::ctrl;

		case VK_RCONTROL:
			return key_code::r_ctrl;

		case VK_LMENU:
			return key_code::alt;

		case VK_RMENU:
			return key_code::r_alt;

		case VK_LSHIFT:
			return key_code::shift;

		case VK_RSHIFT:
			return key_code::r_shift;

		case VK_CAPITAL: 
			return key_code::caps;
		
		case VK_TAB:     
			return key_code::tab;
	
		case VK_SPACE:
			return key_code::space;

		case VK_OEM_2:     
			return key_code::f_slash;
		
		case VK_OEM_5:     
			return key_code::b_slash;

		case VK_OEM_COMMA: 
			return key_code::comma;

		case VK_OEM_PERIOD: 
			return key_code::fullstop;

		case VK_OEM_MINUS: 
			return key_code::hyphen;

		case VK_OEM_PLUS:  
			return key_code::equal;

		case VK_OEM_7: 
			return key_code::apostrophe;

		case VK_OEM_4: 
			return key_code::open_bracket;
		
		case VK_OEM_6: 
			return key_code::close_bracket; 

		case VK_HOME: 
			return key_code::home;		

		case VK_INSERT: 
			return key_code::ins;
		
		case VK_DELETE: 
			return key_code::del;
		
		case VK_END:
			return key_code::end;
		
		case VK_PRIOR:
			return key_code::pg_up;
		
		case VK_NEXT:
			return key_code::pg_dn;

		case VK_UP:
			return key_code::up;

		case VK_DOWN:
			return key_code::down;

		case VK_LEFT:
			return key_code::left;

		case VK_RIGHT:
			return key_code::right;

		case VK_RETURN:
			return key_code::enter;

			
		default:
			return key_code::none;

		}
	}
}

const native_handle* win32_window::get_native_handle() const {
	return &_native_handle;
}

HWND win32_window::get_hwnd() const {
    return _native_handle.handle;
}

END_NS
