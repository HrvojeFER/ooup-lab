#ifndef OOUP_LAB_EXERCISE_3_TASK_1_ANIMAL_FACTORY_H
#define OOUP_LAB_EXERCISE_3_TASK_1_ANIMAL_FACTORY_H



#include "pch.h"


size_t get_animal_type_size(const char* const type);
void construct_animal(const char* const type, struct animal* animal, const char* name);

struct animal* create_animal(const char* type, const char* name);



#endif
