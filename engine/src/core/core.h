#pragma once

#if defined(_WIN32) || defined(__CYGWIN__)

    #ifdef VM_SHARE_BUILD
        #define VANMAM_API __declspec(dllexport)
    #else
        #define VANMAM_API __declspec(dllimport)
    #endif
#else
    #if defined(__GNUC__) || __GNUC__ >= 4
        #define VANMAM_API __attribute((visibility("default")))
    #else
        #define VANMAM_API
    #endif
#endif

#define NS(x) namespace vm::x {
#define NS_VANMAM namespace vm {

#define END_NS }
