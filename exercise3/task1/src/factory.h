#ifndef OOUP_LAB_EXERCISE_3_TASK_1_FACTORY_H
#define OOUP_LAB_EXERCISE_3_TASK_1_FACTORY_H



#define LIBRARY_NOT_FOUND 404
#define FUNCTION_NOT_FOUND 403
#define STACK_ALLOCATION_FAILED 204


size_t get_required_size(const char* library_name);
int construct(const char* library_name, void* object, const char* constructor_argument);

void* create(const char* library_name, const char* constructor_argument);



#endif
