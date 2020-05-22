#include "pch.h"

#include "tiger.h"



struct tiger
{
	const animal_function_pointer* vf_table;
	const char* name;
};


const char* tiger_name(void* tiger)
{
	return ((struct tiger*)tiger)->name;
}

const char* tiger_greeting(void* null)
{
	return "Meow.";
}

const char* tiger_menu(void* null)
{
	return "MEAT!";
}


const animal_function_pointer tiger_vf_table[3] =
{
	tiger_name,
	tiger_greeting,
	tiger_menu
};

void* create_tiger(const char* name)
{
	struct tiger* tiger = (struct tiger*)malloc(sizeof(struct tiger));

	tiger->vf_table = tiger_vf_table;
	tiger->name = name;

	return (void*)tiger;
}
