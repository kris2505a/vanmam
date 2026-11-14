#pragma once
#include "core/core.h"
#include <cstdint>

#include <memory>
#include <string>


#ifdef PF_WINDOWS

#include <windows.h>
#include <wrl/client.h>


#endif


NS_VANMAM

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using f32 = float;
using f64 = double;

template <typename T>
using scope = std::unique_ptr<T>;

template <typename T, typename... Args>
constexpr scope<T> new_scope(Args&&... args) {
    return std::make_unique<T>(args...);
}

template <typename T>
using strong_ref = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr strong_ref<T> new_strong_ref (Args&&... args) {
    return std::make_shared<T>(args...);
}

template <typename T>
using weak_ref = std::weak_ptr<T>;

#ifdef PF_WINDOWS

template <typename T>
using com_ref = Microsoft::WRL::ComPtr<T>;

inline std::string to_narrow(std::wstring_view wstr) {
    if (wstr.empty()) {
        return "";
    }

    const i32 size = WideCharToMultiByte(
        CP_UTF8,
        WC_ERR_INVALID_CHARS,
        wstr.data(),
        static_cast<i32>(wstr.size()),
        nullptr,
        0,
        nullptr,
        nullptr
    );

    if (0 == size) {
        return "";
    }

    std::string out;
    out.resize(size);
	WideCharToMultiByte(
		CP_UTF8,
		WC_ERR_INVALID_CHARS,
		wstr.data(),
		static_cast<i32>(wstr.size()),
		out.data(),
		size,
		nullptr,
		nullptr
	);

    return out;
}

inline std::wstring to_wide(std::string_view str) {
	if (str.empty()) {
		return L"";
	}

	const i32 size = MultiByteToWideChar(
		CP_UTF8,
		MB_ERR_INVALID_CHARS,
		str.data(),
		static_cast<i32>(str.size()),
		nullptr,
		0
	);

	if (0 == size) {
		return L"";
	}

	std::wstring out;
	out.resize(size);

	MultiByteToWideChar(
		CP_UTF8,
		MB_ERR_INVALID_CHARS,
		str.data(),
		static_cast<i32>(str.size()),
		out.data(),
		size
	);

	return out;
}

#endif


END_NS
