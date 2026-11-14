#pragma once
#include "core/core.h"

#ifdef PF_WINDOWS

#include <windows.h>

#endif


NS(pf)

struct native_handle {
	template <typename T>
	T* as() {
		return dynamic_cast<T*>(this);
	}
};

#ifdef PF_WINDOWS 

struct windows_native_handle : native_handle {
	HINSTANCE instance;
	HWND handle;
};

#endif




END_NS
