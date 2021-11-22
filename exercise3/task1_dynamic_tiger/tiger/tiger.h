#ifndef OOUP_LAB_EXERCISE_3_TASK_1_TIGER_DYNAMIC_EXPORT_H
#define OOUP_LAB_EXERCISE_3_TASK_1_TIGER_DYNAMIC_EXPORT_H



#include "pch.h"



#define TIGER_ALLOCATION_FAILED 202
#define TIGER_CAST_FAILED 302


#ifdef __cplusplus
extern "C" {
#endif

	__declspec(dllexport) size_t get_tiger_size();
	__declspec(dllexport) int construct_tiger(void* tiger, const char* name);
	
    __declspec(dllexport) void* create_tiger(const char* name);

#ifdef __cplusplus
}
#endif



#endif
