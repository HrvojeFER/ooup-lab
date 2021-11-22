#include "pch.h"

#include "parrot.h"



struct parrot
{
	const animal_function_pointer* vf_table;
	const char* name;
};



const char* parrot_name(void* parrot)
{
	const struct parrot* parrot_cast = (struct parrot*)parrot;
	if (!parrot_cast)
	{
		exit(PARROT_CAST_FAILED);
	}
	
	return parrot_cast->name;
}

const char* parrot_greeting(void* null)
{
	return "KA KAAAA!";
}

const char* parrot_menu(void* null)
{
	return "Sesame seeds, lettuce and stuff.";
}


const animal_function_pointer parrot_vf_table[3] =
{
	parrot_name,
	parrot_greeting,
	parrot_menu
};



size_t get_parrot_size()
{
	return sizeof(struct parrot);
}

int construct_parrot(void* parrot, const char* const name)
{
	struct parrot* parrot_cast = (struct parrot*)parrot;
	if(!parrot_cast)
	{
		return PARROT_CAST_FAILED;
	}

	parrot_cast->vf_table = parrot_vf_table;
	parrot_cast->name = name;

	return 0;
}



void* create_parrot(const char* const name)
{
	struct parrot* parrot = (struct parrot*)malloc(get_parrot_size());
	if(!parrot)
	{
		exit(PARROT_ALLOCATION_FAILED);
	}

	const int error_code = construct_parrot(parrot, name);
	if (error_code)
	{
		exit(error_code);
	}

	return (void*)parrot;
}
