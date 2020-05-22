#include "pch.h"

#include "tiger.h"



struct tiger
{
	const animal_function_pointer* vf_table;
	const char* name;
};

size_t get_tiger_size()
{
	return sizeof(struct tiger);
}


const char* tiger_name(const void* const tiger)
{
	const struct tiger* const tiger_cast = (struct tiger*)tiger;
	if(!tiger_cast)
	{
		exit(TIGER_CAST_FAILED);
	}
	
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

int construct_tiger(void* tiger, const char* name)
{
	struct tiger* tiger_cast = (struct tiger*)tiger;
	if(!tiger_cast)
	{
		return TIGER_CAST_FAILED;
	}

	tiger_cast->vf_table = tiger_vf_table;
	tiger_cast->name = name;

	return 0;
}

void* create_tiger(const char* name)
{
	struct tiger* tiger = (struct tiger*)malloc(get_tiger_size());
	if(!tiger)
	{
		exit(TIGER_ALLOCATION_FAILED);
	}

	const int error_code = construct_tiger(tiger, name);
	if (error_code)
	{
		exit(error_code);
	}

	return (void*)tiger;
}
