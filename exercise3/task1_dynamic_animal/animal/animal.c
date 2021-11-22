#include "pch.h"

#include "animal.h"



struct animal
{
	const animal_function_pointer* vf_table;
	// vf_table entries:
	// 0: const char* name(void* this);
	// 1: const char* greet();
	// 2: const char* menu();
};


ANIMAL_API const char* animal_name(const struct animal* const animal)
{
    return animal->vf_table[0]((void*)animal);
}

void animal_print_greeting(const struct animal* const animal)
{
    printf("%s\n", animal->vf_table[1](NULL));
}

void animal_print_menu(const struct animal* const animal)
{
    printf("%s\n", animal->vf_table[2](NULL));
}
