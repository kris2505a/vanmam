#pragma once

#include "core/core.h"

#include <new>
#include <utility>

NS_VANMAM

template<typename T_Val, typename T_Err>
class Result {
public:
    ~Result();

    Result(const Result& other) = delete;
    Result& operator=(const Result& other) = delete;

    Result(Result&& other);
    Result& operator=(Result&& other);

    bool has_value() const;

    T_Err& get_error();
    const T_Err& get_error() const;

    T_Val& get_value();
    const T_Val& get_value() const;

    static Result<T_Val, T_Err> success(T_Val value);
    static Result<T_Val, T_Err> failure(T_Err value);

private:
    struct SuccessTag {};
    struct FailureTag {};

    Result(SuccessTag tag, T_Val value);
    Result(FailureTag tag, T_Err error);

    union {
        T_Val _val;
        T_Err _err;
    };

    bool _has_value;
};


// Constructors

template<typename T_Val, typename T_Err>
Result<T_Val, T_Err>::Result(SuccessTag tag, T_Val value)
    : _has_value(true)
{
    new (&_val) T_Val(std::move(value));
}

template<typename T_Val, typename T_Err>
Result<T_Val, T_Err>::Result(FailureTag tag, T_Err error)
    : _has_value(false)
{
    new (&_err) T_Err(std::move(error));
}


// Factory methods

template<typename T_Val, typename T_Err>
Result<T_Val, T_Err>
Result<T_Val, T_Err>::success(T_Val value)
{
    return Result<T_Val, T_Err>(SuccessTag{}, std::move(value));
}

template<typename T_Val, typename T_Err>
Result<T_Val, T_Err>
Result<T_Val, T_Err>::failure(T_Err error)
{
    return Result<T_Val, T_Err>(FailureTag{}, std::move(error));
}


// Accessors

template<typename T_Val, typename T_Err>
bool Result<T_Val, T_Err>::has_value() const
{
    return _has_value;
}

template<typename T_Val, typename T_Err>
T_Err& Result<T_Val, T_Err>::get_error()
{
    return _err;
}

template<typename T_Val, typename T_Err>
const T_Err& Result<T_Val, T_Err>::get_error() const
{
    return _err;
}

template<typename T_Val, typename T_Err>
T_Val& Result<T_Val, T_Err>::get_value()
{
    return _val;
}

template<typename T_Val, typename T_Err>
const T_Val& Result<T_Val, T_Err>::get_value() const
{
    return _val;
}


// Move constructor

template<typename T_Val, typename T_Err>
Result<T_Val, T_Err>::Result(Result&& other)
    : _has_value(other._has_value)
{
    if (_has_value) {
        new (&_val) T_Val(std::move(other._val));
    }
    else {
        new (&_err) T_Err(std::move(other._err));
    }
}


// Move assignment operator

template<typename T_Val, typename T_Err>
Result<T_Val, T_Err>&
Result<T_Val, T_Err>::operator=(Result&& other)
{
    if (this == &other) {
        return *this;
    }

    if (_has_value && other._has_value) {
        _val = std::move(other._val);
    }
    else if (!_has_value && !other._has_value) {
        _err = std::move(other._err);
    }
    else if (_has_value && !other._has_value) {
        _val.~T_Val();
        new (&_err) T_Err(std::move(other._err));
        _has_value = false;
    }
    else {
        _err.~T_Err();
        new (&_val) T_Val(std::move(other._val));
        _has_value = true;
    }

    return *this;
}


// Destructor

template<typename T_Val, typename T_Err>
Result<T_Val, T_Err>::~Result()
{
    if (_has_value) {
        _val.~T_Val();
    }
    else {
        _err.~T_Err();
    }
}

END_NS
