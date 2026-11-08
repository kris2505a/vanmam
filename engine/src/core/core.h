#pragma once

#if defined(_WIN32) || defined(__CYGWIN__)

    #ifdef VM_SHARED_BUILD
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


#ifdef VM_DEBUG 
    #define VM_ASSERT(x) if (!(x)) __debugbreak();
#else
    #define VM_ASSERT(x)
#endif

#define END_NS }
