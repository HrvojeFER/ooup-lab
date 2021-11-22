#ifndef OOUP_LAB_EXERCISE_3_TASK_1_DYNAMIC_ANIMAL_H
#define OOUP_LAB_EXERCISE_3_TASK_1_DYNAMIC_ANIMAL_H



#if defined(_ANIMAL_BUILD_DLL)
	#define ANIMAL_API __declspec(dllexport)
#elif defined(ANIMAL_DLL)
	#define ANIMAL_API __declspec(dllimport)
#else
	#define ANIMAL_API
#endif


#define ANIMAL_ALLOCATION_FAILED 200
#define ANIMAL_CAST_FAILED 300



#ifdef __cplusplus
extern "C" {
#endif

	ANIMAL_API typedef const char* (*animal_function_pointer)(void*);
	struct ANIMAL_API animal;
	
	ANIMAL_API const char* animal_name(const struct animal* animal);
	ANIMAL_API void animal_print_greeting(const struct animal* animal);
	ANIMAL_API void animal_print_menu(const struct animal* animal);

#ifdef __cplusplus
}
#endif



#endif
