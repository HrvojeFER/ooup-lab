#include "pch.h"

#include "parrot.h"



struct parrot
{
	const animal_function_pointer* vf_table;
	const char* name;
};


const char* parrot_name(void* parrot)
{
	return ((struct parrot*)parrot)->name;
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

void* create_parrot(const char* const name)
{
	struct parrot* parrot = (struct parrot*)malloc(sizeof(struct parrot));

	parrot->vf_table = parrot_vf_table;
	parrot->name = name;

	return (void*)parrot;
}
