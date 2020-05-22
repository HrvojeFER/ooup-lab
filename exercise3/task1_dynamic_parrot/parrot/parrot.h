#ifndef OOUP_LAB_EXERCISE_3_TASK_1_TIGER_DYNAMIC_EXPORT_H
#define OOUP_LAB_EXERCISE_3_TASK_1_TIGER_DYNAMIC_EXPORT_H



#include "pch.h"



#ifdef __cplusplus
extern "C" {
#endif

    __declspec(dllexport) void* create_parrot(const char* name);

#ifdef __cplusplus
}
#endif



#endif
