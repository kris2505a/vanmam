#pragma once
#include "core/core.h"
#include <cstdint>

#include <memory>


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


END_NS
