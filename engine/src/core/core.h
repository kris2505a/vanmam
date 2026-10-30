#pragma once

#ifdef VM_SHARE_BUILD
    #define VANMAM_API __declspec(dllexport)
#else
    #define VANMAM_API __declspec(dllimport)
#endif


#define NS(x) namespace vm::x {
#define NS_VANMAM namespace vm {

#define END_NS }
