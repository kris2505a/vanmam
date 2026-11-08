#pragma once
#include "platform/window.h"

#include <Windows.h>

NS(pf)

class win32_window : public window {
public:
	win32_window(u32 width, u32 height, std::string_view title);
	~win32_window();
	void poll_events() override;

	void setup_window_class();
	void create_window();
	HWND get_handle() const;
	void show_window();

private:
	static LRESULT CALLBACK win_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);


private:
	HWND _handle;
	HINSTANCE _instance;
	WNDCLASSEXA	_window_class;
	std::string _class_name;

};

END_NS