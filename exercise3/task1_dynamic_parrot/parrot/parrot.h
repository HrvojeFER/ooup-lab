#ifndef OOUP_LAB_EXERCISE_3_TASK_1_TIGER_DYNAMIC_EXPORT_H
#define OOUP_LAB_EXERCISE_3_TASK_1_TIGER_DYNAMIC_EXPORT_H



#include "pch.h"



#define PARROT_ALLOCATION_FAILED 201
#define PARROT_CAST_FAILED 301


#ifdef __cplusplus
extern "C" {
#endif

	__declspec(dllexport) size_t get_parrot_size();
	__declspec(dllexport) int construct_parrot(void* parrot, const char* name);
	
    __declspec(dllexport) void* create_parrot(const char* name);

#ifdef __cplusplus
}
#endif



#endif
