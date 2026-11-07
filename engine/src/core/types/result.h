#pragma once

#include "core/core.h"

#include <new>
#include <utility>

NS_VANMAM

template<typename T_Val, typename T_Err>
class result {
public:
    ~result() {
        if (_has_value) {
            _val.~T_Val();
        }
        else {
            _err.~T_Err();
        }
    }

    result(const result& other) = delete;
    result& operator=(const result& other) = delete;

    result(result&& other) 
        : _has_value(other._has_value) {
        if (_has_value) {
            new (&_val) T_Val(std::move(other._val));
        }
        else {
            new (&_err) T_Err(std::move(other._err));
        }
    }

    result& operator=(result&& other) {
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

    bool has_value() const {
        return _has_value;
    }

    T_Err&& get_error() {
        return std::move(_err);
    }

    T_Val&& get_value() {
        return std::move(_val);
    }

    static result<T_Val, T_Err> success(T_Val value) {
        result res(true);
        new(&res._val) T_Val(std::move(value));
        return res;
    }

    static result<T_Val, T_Err> failure(T_Err error) {
        result res(false);
        new(&res._err) T_Err(std::move(error));
        return res;
    }

private:

    result(bool value) : _has_value(value) {}  
    
    union {
        T_Val _val;
        T_Err _err;
    };

    bool _has_value;
};

END_NS
